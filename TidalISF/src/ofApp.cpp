#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    for (int i = 0; i < layerNum; i++) {
        ofxTidalISF *ti = new ofxTidalISF(i);
        tidalISFs.push_back(ti);
    }
    
    //OSC
    receiver.setup(PORT);
    ofAddListener(receiver.messageReceived, this, &ofApp::oscReceiveEvent);
    receiver.start();}


void ofApp::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/play"){
        string name = m.getArgAsString(0);
        int l = m.getArgAsInt(3);
        tidalISFs[l]->currentISF = name;
        tidalISFs[l]->gain = m.getArgAsFloat(2);
        for (int i = 0; i < tidalISFs[l]->isfDirts.size(); i++) {
            tidalISFs[l]->isfDirts[i]->isf->setUniform<float>("vel", m.getArgAsFloat(1));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < tidalISFs.size(); i++) {
        tidalISFs[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < tidalISFs.size(); i++) {
        tidalISFs[i]->draw();
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
