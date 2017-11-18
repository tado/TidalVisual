#include "ofApp.h"
//#include "StISFView.hpp"
#include "StSyncopationMonitor.hpp"
#include "StSyncopationMonitorColor.hpp"
#include "St3DVisalizer.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_SILENT);
    tidal = new ofxTidalView(3333);

	//stateMachine.addState<StISFView>();
	stateMachine.addState<StSyncopationMonitor>();
	stateMachine.addState<StSyncopationMonitorColor>();
	stateMachine.addState<St3DVisalizer>();
	stateMachine.changeState("StSyncopationMonitorColor");
}

void ofApp::update(){
    
}

void ofApp::draw(){
    
}

void ofApp::oscEvent(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        stateMachine.changeState("StSyncopationMonitorColor");

    }
	/*
    if (key == '2') {
        stateMachine.changeState("StISFView");
    }
	*/
    if (key == '2') {
        stateMachine.changeState("St3DVisalizer");
    }
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
