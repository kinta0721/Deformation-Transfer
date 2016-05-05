#include "mesh.h"
#include "math_headers.h"
#include <Eigen/Householder>
#include <Eigen/Eigen>
#include <Eigen/Eigenvalues> 
#include <Eigen/SparseLU>
//#include <Eigen /OrderingMethodsz>
#pragma region Mesh

using namespace std;
void Mesh::Reset() {
	Cleanup();
	Init();
}

void Mesh::Cleanup() {
}



void Mesh::computeNormal() { //–@ü•ûŒü‚ÌŒvZ
	std::cout << "computing normals..." << std::endl;

	// reset all the normal
	m_N.setZero();

	// calculate normal for each individual triangle
	unsigned int triangle_num = getTriNum();
	unsigned int id0, id1, id2;
	EigenVector3 p0, p1, p2;
	EigenVector3 normal;
	for (unsigned int i = 0; i < triangle_num; ++i)
	{
		id0 = m_F(i, 0);
		id1 = m_F(i, 1);
		id2 = m_F(i, 2);

		p0 = m_V.row(id0).transpose();
		p1 = m_V.row(id1).transpose();
		p2 = m_V.row(id2).transpose();

		normal = (p1 - p0).cross(p2 - p1);
		normal.normalize();

		m_N.row(id0) += normal.transpose();
		m_N.row(id1) += normal.transpose();
		m_N.row(id2) += normal.transpose();

	}
	// re-normalize all the normals.
	for (int i = 0; i < m_N.rows(); i++)
	{
		if (m_N.row(i).norm() > EPSILON)
			m_N.row(i).normalize();

		//std::cout << m_N.row(i) << std::endl;
	}


}




bool Mesh::Init() {
	std::cout << "Init Mesh..." << std::endl;

	computeNormal();

	return true;
}

void Mesh::Makeidealaffine(EigenMatrixXs  &F, const Mesh *copied) {

	F.resize(getTriNum() * 3, 3);
	unsigned int id0, id1, id2, _id0, _id1, _id2;
	EigenVector3 p0, p1, p2, _p0, _p1, _p2;
	EigenMatrix3  S, _S;


	EigenMatrixXs _m_V;
	EigenMatrixXi _m_F;
	
	
	_m_V = copied->getm_V();
	_m_F = copied->getm_F();


	for (int i = 0; i < getTriNum(); ++i) {

		EigenVector3 p3, _p3;

		id0 = m_F(i, 0);
		id1 = m_F(i, 1);
		id2 = m_F(i, 2);

		p0 = m_V.row(id0).transpose();
		p1 = m_V.row(id1).transpose();
		p2 = m_V.row(id2).transpose();


		_id0 = _m_F(i, 0);
		_id1 = _m_F(i, 1);
		_id2 = _m_F(i, 2);

		_p0 = _m_V.row(id0).transpose();
		_p1 = _m_V.row(id1).transpose();
		_p2 = _m_V.row(id2).transpose();



		p3 = MakePos4(p0, p1, p2);//x4ì‚é
		_p3 = MakePos4(_p0, _p1, _p2);//x4ì‚é

		MakeMatrix33(p0, p1, p2, p3, S);
		MakeMatrix33(_p0, _p1, _p2, _p3, _S);


		F.block(3 * i, 0, 3, 3) = (_S*(S.inverse())).transpose();//‚eì‚é

	}


}

void Mesh::MakingA(SparseMartix &A) {

	unsigned int id0, id1, id2;
	EigenVector3 p0, p1, p2;
	EigenMatrix23 rq;
	EigenMatrix32 qr;



	A.resize(3 * getTriNum(), getVertNum());


	std::vector<T> triplets;




	for (int i = 0; i < getTriNum(); ++i) {
		id0 = m_F(i, 0);
		id1 = m_F(i, 1);
		id2 = m_F(i, 2);

		p0 = m_V.row(id0).transpose();
		p1 = m_V.row(id1).transpose();
		p2 = m_V.row(id2).transpose();



		MakeMatrix32(p0, p1, p2, qr);
		
		wantQR(qr, rq);

		//std::cout << rq << std::endl;
		triplets.push_back(T(3 * i, id0,-rq(0, 0) - rq(1, 0)));
		triplets.push_back(T(3 * i, id1,rq(0, 0)));
		triplets.push_back(T(3 * i, id2, rq(1, 0)));
		triplets.push_back(T(3 * i + 1, id0, -rq(0, 1) - rq(1, 1)));
		triplets.push_back(T(3 * i + 1, id1,rq(0, 1)));
		triplets.push_back(T(3 * i + 1, id2,rq(1, 1)));
		triplets.push_back(T(3 * i + 2, id0,-rq(0, 2) - rq(1, 2)));
		triplets.push_back(T(3 * i + 2, id1, rq(0, 2)));
		triplets.push_back(T(3 * i + 2, id2, rq(1, 2)));



	}


	A.setFromTriplets(triplets.begin(), triplets.end());

}



void Mesh::SolveForV(EigenMatrixXs  &F, SparseMatrix &A, const Mesh *copied) {
	using namespace Eigen;
	using namespace std;

	EigenVectorX x;
	int type = getVertNum();
	SimplicialCholesky<Eigen::SparseMatrix<double> > solver(A.transpose()*A);//	SparseLU<SparseMatrix<scalar, ColMajor>, COLAMDOrdering<Index>> solver;
	


	m_V = solver.solve((A.transpose())*F);
	m_F = copied->getm_F();
	m_N = copied->getm_N();

	

	
}
void Mesh::wantQR(EigenMatrix32 &A, EigenMatrix23 &N) {//‚p‚q•ª‰ğ‚ğ‚·‚é
	EigenMatrix3 Q,QT;
	EigenMatrix3 H;
	EigenMatrix2 thinR;
	EigenMatrix32 thinQ;
	EigenMatrix32 R;
	EigenMatrixXs E = EigenMatrixXs::Identity(3, 3);
	EigenMatrixXs input = EigenMatrixXs::Identity(3, 3);
	EigenMatrixXs inputE = EigenMatrixXs::Identity(3, 3);
	EigenVectorX I;
	EigenVectorX u, x, y;
	R = A;
	Q = E;
	H = E;
	for (int i = 0; i < 2; i++) {
		x.resize(3 - i, 1);
		y.resize(3 - i, 1);
		input.resize(3 - i, 3 - i);
		
		I.resize(3 - i, 1);
		I.setZero();
		I(0, 0) = 1;
		
		inputE.resize(3-i,3- i);
		inputE.setZero();
		for (int j = 0; j < inputE.cols(); j++) {

			inputE(j, j) = 1;
		}
		

		x = R.block(i, i, 3 - i, 1);
		y = x.norm()*I;

		if (x(0, 0)*y(0, 0)>0) y(0, 0) = y(0, 0)*(-1);

		u = (x - y) / (x - y).norm();
		

		input = inputE - (2 * (u*u.transpose()));
		
		H.setZero();
		for (int j = 0; j < H.cols(); j++) {

			H(j, j) = 1;
		}


		H.block(i, i,3-i,3-i) = input;
		
		R = H*R;
		Q = H*Q;





	}

	
	QT = Q.transpose();
	thinQ = QT.block(0, 0, 3, 2);
	thinR = R.block(0, 0, 2, 2);
	N = (thinR.inverse())*(thinQ.transpose());


}






void  Mesh::MakeMatrix33(EigenVector3 & x_1, EigenVector3 & x_2, EigenVector3 & x_3, EigenVector3 & x_4, EigenMatrix3 & M) {//‘Š‘ÎƒxƒNƒgƒ‹‚ğì‚é

	M.col(0) = x_2 - x_1;
	M.col(1) = x_3 - x_1;
	M.col(2) = x_4 - x_1;

}



EigenVector3 Mesh::MakePos4(EigenVector3 &  x_1, EigenVector3 & x_2, EigenVector3 & x_3) {

	EigenVector3 x_4;
	x_4 = x_1 + ((x_2 - x_1).cross(x_3 - x_1)) / ((x_2 - x_1).cross(x_3 - x_1)).norm();
	return x_4;

}



void Mesh::MakeMatrix32(EigenVector3 & x_1, EigenVector3 & x_2, EigenVector3 & x_3, EigenMatrix32 & M) {

	M.col(0) = x_2 - x_1;
	M.col(1) = x_3 - x_1;
}




#include "GL/glut.h"





void Mesh::renderMesh() {
	glLineWidth(0.3);
	for (int i = 0; i < getTriNum(); ++i)
	{
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 3; ++j)
		{
			int VertIndex = m_F(i, j);

			GLdouble normal[3] = { m_N(VertIndex, 0), m_N(VertIndex, 1), m_N(VertIndex, 2) };
			glNormal3dv(normal);

			glVertex3f(m_V(VertIndex, 0), m_V(VertIndex, 1), m_V(VertIndex, 2));
		}
		glEnd();
	}
}

	void Mesh::renderPoly() {
		glLineWidth(0.3);
		for (int i = 0; i < getTriNum(); ++i)
		{
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < 3; ++j)
			{
				int VertIndex = m_F(i, j);

				GLdouble normal[3] = { m_N(VertIndex, 0), m_N(VertIndex, 1), m_N(VertIndex, 2) };
				glNormal3dv(normal);

				glVertex3f(m_V(VertIndex, 0), m_V(VertIndex, 1), m_V(VertIndex, 2));
			}
			glEnd();
		}
	}

#include <igl/read_triangle_mesh.h>

	void Mesh::read_from_file(std::string filename) {

		std::cout << "reading Obj file through libigl..." << std::endl;

		igl::readOBJ(filename, m_V, m_F);

		// adjust scaling
		m_scaling = 50.0;
		m_V *= m_scaling;

		// resize normal Mat
		m_N.resize(getVertNum(), 3);

	}

#pragma endregion