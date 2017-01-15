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
    
    //draw matrix
    ofSetColor(255, 127, 127);
    for (int i = 0; i < app->tidal->notes.size(); i++) {
        if(app->tidal->notes[i].syncCount == app->tidal->syncCount){
            float x = ofMap(app->tidal->notes[i].beatCount, 0, app->tidal->resolution*4, 0, width);
            float h;
            if(app->tidal->instBuffer.size() == 0){
                h = 0;
            } else {
                h = height / app->tidal->instBuffer.size();
            }
            float y = h * app->tidal->notes[i].instNum;
            ofDrawRectangle(x, y, width/app->tidal->resolution/12.0, h);
        }
    }
    ofSetColor(255);
    if (app->tidal->syncCount > 0) {
        for (int i = 0; i <= app->tidal->instNumMax; i++) {
            for (int j = 0; j < 64; j++) {
                if (app->tidal->noteMatrix[i][j] == 1) {
                    int x = ofMap(j, 0, 64, 0, width);
                    int h = height / (app->tidal->instNumMax + 1);
                    float y = h * i;
                    ofDrawRectangle(x, y, width/app->tidal->resolution/12.0, h);
                }
            }
        }
    }
    ofPopMatrix();

    //draw graph
    float x, y, width, height, graphX;
    float graphWidth;
    x = 20;
    y = ofGetHeight()/2 + 20;
    graphX = 50;
    width = ofGetWidth() - 40 - graphX;
    height = 15;
    
    ofTranslate(x, y);
    ofPushMatrix();
    for (int i = 0; i <= app->tidal->instNumMax; i++) {
        ofTranslate(0, 20);
        graphWidth = ofMap(app->tidal->syncopation[i], 0, 15, 0, width);
        ofSetColor(63);
        ofDrawRectangle(graphX, 0, width, height);
        ofSetColor(63, 127, 255);
        ofDrawRectangle(graphX, 0, graphWidth, height);
        ofSetColor(255);
        ofDrawBitmapString("S"
                           + ofToString(i) + ":"
                           + ofToString(app->tidal->syncopation[i]), 0, 10);
    }
    ofPopMatrix();
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
