#pragma once

#include "iostream"
#include "math_headers.h"
#include "st.h"

typedef enum {
	MESH_TYPE_OBJ,
	MESH_TYPE_TOTAL_NUM
} MeshType;

class Mesh {
public:
	Mesh() : m_mesh_type() {}
	Mesh(MeshType mesh_type) : m_mesh_type(mesh_type) {}
	virtual ~Mesh() { Cleanup(); }

	void Reset();
	bool Init();
	virtual void Cleanup();

protected:
	MeshType m_mesh_type;

	EigenMatrixXs m_V0;	// rest pose
	EigenMatrixXs m_V;	// current pose
	EigenMatrixXs m_N;	// current 
	EigenMatrixXi m_F;  // tri index
	EigenMatrixXi m_T;  // tet index
	float m_scaling;

public:	// get method
	int getVertNum() const { return (int)m_V.rows(); }
	int getTriNum()  const { return (int)m_F.rows(); }
	int getTetNum()  const { return (int)m_T.rows(); }
	EigenMatrixXi getm_F()  const { return (EigenMatrixXi)m_F; }
	EigenMatrixXs getm_N()	const { return (EigenMatrixXs)m_N; }
	EigenMatrixXs getm_V()	const { return (EigenMatrixXs)m_V; }


	//Setmethod


	//void computeNormal();


	void renderMesh();
	void renderPoly();
	void read_from_file(std::string filename);

	
	void MakeMatrix33(EigenVector3 & x_1, EigenVector3 & x_2, EigenVector3 & x_3, EigenVector3 & x_4, EigenMatrix3 & M);
	void MakeMatrix32(EigenVector3 & x_1, EigenVector3 & x_2, EigenVector3 & x_3, EigenMatrix32 & M);
	EigenVector3 MakePos4(EigenVector3 &  x_1, EigenVector3 & x_2, EigenVector3 & x_3);

	void Makeidealaffine(EigenMatrixXs  &F, const Mesh *copied);
	void MakingA(SparseMartix &A);
	void SolveForV(EigenMatrixXs  &F, SparseMatrix &A, const Mesh *copy);


	void wantQR(EigenMatrix32 &a, EigenMatrix23 &N);

	void computeNormal();

};