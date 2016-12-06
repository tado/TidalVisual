#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    //ofDisableSmoothing();
    ofSetLineWidth(3.0);
    //OSC
    receiver.setup(3333);
    ofAddListener(receiver.messageReceived, this, &ofApp::oscReceiveEvent);
    receiver.start();
    started = false;
    startTime = 0;
    span = 0.08;
    ofSetLogLevel(OF_LOG_SILENT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    for (int i = 0; i < currents.size(); i++) {
        ofDrawLine(currents[i]*span, 0, currents[i]*span, 100);
        if(currents[i]*span > ofGetWidth()){
            currents.clear();
            startTime = ofGetElapsedTimeMillis();
            break;
        }
    }
}

void ofApp::oscReceiveEvent(ofxOscMessage &m){
    //ISF
    if(m.getAddress() == "/play2"){
        if (startTime == 0) {
            startTime = ofGetElapsedTimeMillis();
        }
        float currentTime = ofGetElapsedTimeMillis() - startTime;
        currents.push_back(currentTime);
        string inst = "";
        for (int i = 0; i < m.getNumArgs(); i++) {
            if(m.getArgAsString(i) == "s"){
                inst = m.getArgAsString(i+1);
            }
        }
        int instNameFounded = -1;
        for (int i = 0; i < instNames.size(); i++) {
            if(instNames[i] == inst){
                instNameFounded = i;
            }
        }
        if (instNameFounded == -1) {
            instNames.push_back(inst);
        }
        
        for (int i = 0; i < instNames.size(); i++) {
            cout << instNames[i] << " ";
        }
        cout << endl;
        /*
         << " " << m.getArgAsString(0)
         << " " << m.getArgAsFloat(1)
         << " " << m.getArgAsString(2)
         << " " << m.getArgAsString(3)
         << endl;
         */
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
