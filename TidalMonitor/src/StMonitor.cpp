#include "StMonitor.hpp"

void StMonitor::setup(){
    name = "StMonitor";
    app = ((ofApp*)ofGetAppPtr());
    top = 20;
    left= 20;
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
}

void StMonitor::update(){

}

void StMonitor::draw(){
    ofPushMatrix();
    ofTranslate(top, left);

    drawGrid();

    ofSetColor(255);
    for (int i = 0; i < app->osc->notes.size(); i++) {
        float x = ofMap(app->osc->notes[i].beatCount, 0, 32, 0, width);
        float h = height / app->osc->instNames.size();
        float y = h * app->osc->notes[i].instNum;
        ofDrawRectangle(x, y, width/256.0, h);
    }
    ofPopMatrix();
    
    ofDrawBitmapString("Note num (per cycle) = " + ofToString(app->osc->totalNoteCount), 20, ofGetHeight()/2);
    ofDrawBitmapString("Syncopation score = " + ofToString(app->osc->syncopationScore), 20, ofGetHeight()/2 + 20);
}

void StMonitor::drawGrid(){
    ofSetColor(63);
    for (int i = 0; i < 32; i++) {
        float x = ofMap(i, 0, 32, 0, width);
        ofDrawLine(x, 0, x, height);
    }
    ofSetColor(127);
    for (int i = 0; i < 8; i++) {
        float x = ofMap(i, 0, 8, 0, width);
        ofDrawLine(x, 0, x, height);
    }
    ofSetColor(191);
    ofNoFill();
    ofDrawRectangle(0, 0, width, height);
    ofFill();
}

void StMonitor::stateExit(){

}

void StMonitor::stateEnter(){

}

string StMonitor::getName(){
    return name;
}
