#include "SyncopationMonitor.hpp"

void SyncopationMonitor::setup(){
    name = "SyncopationMonitor";
    app = ((ofApp*)ofGetAppPtr());
    top = 20;
    left= 20;
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    count = 0;
}

void SyncopationMonitor::update(){
    
}

void SyncopationMonitor::draw(){
    ofPushMatrix();
    ofTranslate(top, left);
    
    drawGrid();
    
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(app->tidal->syncCount * width/8, 0);

    for (int i = 0; i < app->tidal->instNumMax+1; i++) {
        for (int j = 0; j < 16; j++) {
            if (app->tidal->noteMatrix[i][j] == 1) {
                int x = ofMap(j, 0, 16, 0, width / 8);
                int h = height / (app->tidal->instNumMax + 1);
                float y = h * i;
                ofDrawRectangle(x, y, 3, h-2);
            }
        }
    }
    ofPopMatrix();
        
    ofPopMatrix();
    
    float x, y, width, height;
    float graphWidth;
    
    x = 20;
    y = ofGetHeight()/2 + 20;
    width = ofGetWidth() - 40;
    height = 20;
    
    graphWidth = ofMap(app->tidal->notePerCycle, 0, 100, 0, width);
    ofSetColor(63);
    ofDrawRectangle(x, y, width, height);
    ofSetColor(63, 127, 255);
    ofDrawRectangle(x, y, graphWidth, height);
    ofSetColor(255);
    ofDrawBitmapString("Note num (per cycle) = " + ofToString(app->tidal->notePerCycle), 20, ofGetHeight()/2 + 15);
    
    y = ofGetHeight()/2 + 70;
    graphWidth = ofMap(app->tidal->syncopationPerCycle, 0.0, 8.0, 0, width);
    ofSetColor(63);
    ofDrawRectangle(x, y, width, height);
    ofSetColor(255, 127, 63);
    ofDrawRectangle(x, y, graphWidth, height);
    ofSetColor(255);
    ofDrawBitmapString("Syncopation score = " + ofToString(app->tidal->syncopationPerCycle), 20, ofGetHeight()/2 + 65);
}

void SyncopationMonitor::drawGrid(){
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

void SyncopationMonitor::stateExit(){
    
}

void SyncopationMonitor::stateEnter(){
    
}

string SyncopationMonitor::getName(){
    return name;
}
