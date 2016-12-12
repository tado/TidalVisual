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
    
    for (int i = 0; i < app->tidal->notes.size(); i++) {
        float x = ofMap(app->tidal->notes[i].beatCount, 0, app->tidal->resolution*8, 0, width);
        float h;
        if(app->tidal->instBuffer.size() == 0){
            h = 0;
        } else {
            h = height / app->tidal->instBuffer.size();
        }
        float y = h * app->tidal->notes[i].instNum;
        ofDrawRectangle(x, y, width/app->tidal->resolution/16.0, h);
    }

    ofPopMatrix();
    
    float x, y, width, height;
    float graphWidth;
    
    x = 20;
    y = ofGetHeight()/2 + 20;
    width = ofGetWidth() - 40;
    height = 20;
    
    /*
     graphWidth = ofMap(app->tidal->totalNoteCount, 0, 200, 0, width);
     ofSetColor(63);
     ofDrawRectangle(x, y, width, height);
     ofSetColor(63, 127, 255);
     ofDrawRectangle(x, y, graphWidth, height);
     
     y = ofGetHeight()/2 + 70;
     graphWidth = ofMap(app->tidal->syncopationScore, 5.0, 0.0, 0, width);
     ofSetColor(63);
     ofDrawRectangle(x, y, width, height);
     ofSetColor(255, 127, 63);
     ofDrawRectangle(x, y, graphWidth, height);
     
     ofSetColor(255);
     ofDrawBitmapString("Note num (per cycle) = " + ofToString(app->tidal->totalNoteCount), 20, ofGetHeight()/2 + 15);
     ofDrawBitmapString("Syncopation score = " + ofToString(5 - app->tidal->syncopationScore), 20, ofGetHeight()/2 + 65);
     */
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
