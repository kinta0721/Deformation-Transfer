#include "ofApp.h"

EigenMatrixXs  F;
SparseMatrix  A;
EigenMatrix3  S, _S;

namespace {
	std::string obj_file_pass_a = "./data/kawai_N.obj";
	std::string obj_file_pass_b = "./data/kawai_a.obj";
	std::string obj_file_pass_c = "./data/mizo_N.obj";

}

//--------------------------------------------------------------
void ofApp::setup() {

	// mesh setting 

	s_mesh = new Mesh();
	s_mesh->read_from_file(obj_file_pass_a);
	s_mesh->Init();


	s_d_mesh = new Mesh();
	s_d_mesh->read_from_file(obj_file_pass_b);
	s_d_mesh->Init();


	t_mesh = new Mesh();
	t_mesh->read_from_file(obj_file_pass_c);
	t_mesh->Init();

	
	t_d_mesh = new Mesh();
	t_d_mesh->Init();



	
	s_mesh->Makeidealaffine(F, s_d_mesh);
	t_mesh->MakingA(A);
	t_d_mesh->SolveForV(F, A, t_mesh);

	t_d_mesh->computeNormal();

	// lights settng 
	lights.resize(2);
	float light_distance = 300.;
	lights[0].setPosition(2.0*light_distance, 1.0*light_distance, 0.);
	lights[1].setPosition(-2.0*light_distance, -1.0*light_distance, 1.0* light_distance);



}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackgroundGradient(ofColor(100), ofColor(25));

	glEnable(GL_DEPTH_TEST);

	ofEnableLighting();
	for (int i = 0; i < lights.size(); ++i) { lights[i].enable(); }

	cam.begin(); //@@@@@@@@@@@@@@@@@@@@
	ofPushMatrix();

	ofSetColor(ofColor(133, 180, 250));

	glTranslatef(-100, 100,0);
	s_mesh->renderPoly();
		
	glTranslatef(200,0,0);
	s_d_mesh->renderPoly();

	glTranslatef(-200, -200,0);
	t_mesh->renderPoly();

	glTranslatef(200, -20,0);
	t_d_mesh->renderPoly();


	ofPopMatrix();
	cam.end();   //@@@@@@@@@@@@@@@@@@@@

	for (int i = 0; i < lights.size(); i++) { lights[i].disable(); }
	ofDisableLighting();
	glDisable(GL_DEPTH_TEST);





}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
