#include "StMonitor.hpp"

void StMonitor::setup(){
    name = "StMonitor";
    app = ((ofApp*)ofGetAppPtr());
}

void StMonitor::update(){

}

void StMonitor::draw(){
    drawGrid();
    ofSetColor(255);
    for (int i = 0; i < app->osc->notes.size(); i++) {
        float x = ofMap(app->osc->notes[i].beatCount, 0, 32, 0, ofGetWidth());
        //float y = ofMap(app->osc->notes[i].instNum, 0, app->osc->instNames.size(), 0, ofGetWidth());
        float height = ofGetHeight() / app->osc->instNames.size();
        float y = height * app->osc->notes[i].instNum;
        ofDrawRectangle(x, y, ofGetWidth()/256.0, height);
    }
    
}

void StMonitor::drawGrid(){
    ofSetColor(63);
    for (int i = 0; i < 32; i++) {
        float x = ofMap(i, 0, 32, 0, ofGetWidth());
        ofDrawLine(x, 0, x, ofGetHeight());
    }
    ofSetColor(127);
    for (int i = 0; i < 8; i++) {
        float x = ofMap(i, 0, 8, 0, ofGetWidth());
        ofDrawLine(x, 0, x, ofGetHeight());
    }
}

void StMonitor::stateExit(){

}

void StMonitor::stateEnter(){

}

string StMonitor::getName(){
    return name;
}
