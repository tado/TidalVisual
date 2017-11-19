#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	receiver.setup(PORT);
	ofSetFrameRate(60);
	ofBackground(0);
	lastBar = 0;
	barBufferNum = 8;
}

//--------------------------------------------------------------
void ofApp::update() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		float cycle;
		//parse when tidal cycle message comming
		if (m.getAddress() == "/play2") {
			TidalNote note;
			note.timeStamp = ofGetElapsedTimef();
			for (int i = 0; i < m.getNumArgs(); i += 2) {
				//parse cycle
				float bar, fract;
				if (m.getArgAsString(i) == "cycle") {
					cycle = m.getArgAsFloat(i + 1);
					note.cycle = cycle;
					fract = modf(cycle, &bar);
					note.bar = int(bar);
					note.fract = fract;
					lastBar = int(bar);
				}
				//parse inst name
				if (m.getArgAsString(i) == "s") {
					note.instName = m.getArgAsString(i + 1);
					bool newInst = true;
					for (int i = 0; i < instNameBuffer.size(); i++) {
						if (note.instName == instNameBuffer[i]) {
							newInst = false;
							note.instNum = i;
						}
					}
					if (newInst) {
						instNameBuffer.push_back(note.instName);
						std::sort(instNameBuffer.begin(), instNameBuffer.end());
						note.instNum = instNameBuffer.size() - 1;
					}
				}
				//get latency
				if (m.getArgAsString(i) == "latency") {
					note.latency = m.getArgAsFloat(i + 1);
				}
			}
			notes.push_back(note);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//draw notes
	for (int i = 0; i < notes.size(); i++) {
		float height = ofGetHeight() / (instNameBuffer.size());
		float width = ofGetWidth() / 32.0 / barBufferNum;
		float x = (notes[i].cycle - lastBar + barBufferNum -1) * ofGetWidth() / barBufferNum;
		float y = height * notes[i].instNum;
		if (ofGetElapsedTimef() - notes[i].timeStamp > notes[i].latency){
			ofDrawRectangle(x, y, width, height);
		}
	}
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
