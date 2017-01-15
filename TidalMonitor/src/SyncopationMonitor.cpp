#include "SyncopationMonitor.hpp"

void SyncopationMonitor::setup(){
    name = "SyncopationMonitor";
    app = ((ofApp*)ofGetAppPtr());
    top = 20;
    left= 20;
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    lastCount = 0;
}

void SyncopationMonitor::update(){

}

void SyncopationMonitor::draw(){
    ofPushMatrix();
    ofTranslate(top, left);
    
    drawGrid();
    
    ofSetColor(255);
    /*
    if (app->tidal->syncCount < lastCount) {
        //init matrix
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 64; j++) {
                app->tidal->noteMatrix[i][j] = 0;
            }
        }
    }
    lastCount = app->tidal->syncCount;
    */

    //draw matrix
    for (int i = 0; i < app->tidal->instNumMax+1; i++) {
        for (int j = 0; j < 64; j++) {
            if (app->tidal->noteMatrix[i][j] == 1) {
                int x = ofMap(j, 0, 64, 0, width);
                int h = height / (app->tidal->instNumMax + 1);
                float y = h * i;
                ofDrawRectangle(x, y, 3, h-2);
            }
        }
    }
    ofPopMatrix();
    
    float x, y, width, height;
    float graphWidth;
    
    x = 20;
    y = ofGetHeight()/2 + 20;
    width = ofGetWidth() - 40;
    height = 20;
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
