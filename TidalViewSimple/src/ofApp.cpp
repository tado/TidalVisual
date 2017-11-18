#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	receiver.setup(PORT);
	//ofSetLogLevel(OF_LOG_SILENT);
	ofSetFrameRate(60);
	ofBackground(0);
	lastCycleCount = 0;
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
			for (int i = 1; i < m.getNumArgs(); i += 2) {
				//parse cycle
				float cycleCount, fract;
				if (m.getArgAsString(i) == "cycle") {
					cycle = m.getArgAsFloat(i + 1);
					fract = modf(cycle, &cycleCount);
					//update bar
					if (cycleCount > lastCycleCount) {
						notes.clear();
						//clear inst name buffer
						if (int(cycleCount) % 8 == 0) {
							instNameBuffer.clear();
						}
					}
					note.fract = fract;
					lastCycleCount = int(cycleCount);
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
		float width = ofGetWidth() / 128.0;
		ofDrawRectangle(ofGetWidth() * notes[i].fract, height * notes[i].instNum, width, height);
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
