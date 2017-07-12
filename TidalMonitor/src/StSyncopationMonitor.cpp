#include "StSyncopationMonitor.hpp"

void StSyncopationMonitor::setup(){
    name = "StSyncopationMonitor";
    app = ((ofApp*)ofGetAppPtr());
    top = 20;
    left= 20;
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    //lastCount = 0;
    for (int i = 0; i < 128; i++) {
        instNames[i] = "";
    }
}

void StSyncopationMonitor::update(){
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
}

void StSyncopationMonitor::draw(){
    ofPushMatrix();
    ofTranslate(top, left);
    drawGrid();
    ofDisableAlphaBlending();
    
    //draw matrix
    if (app->tidal->instNumMax > 0) {
        ofSetColor(255, 127, 63);
        for (int i = 0; i < app->tidal->notes.size(); i++) {
            float x = ofMap(app->tidal->notes[i].beatCount+48, 0, app->tidal->resolution*4, 0, width);
            float h = height / (app->tidal->instNumMax);
            float y = (h * app->tidal->notes[i].instNum);
            if (y > height - (h/2)) {
                y = 0;
            }
            ofDrawRectangle(x, y, width/app->tidal->resolution/12.0, h);
            instNames[app->tidal->notes[i].instNum] = app->tidal->notes[i].instName;
        }
        for (int i = 0; i < app->tidal->instNumMax; i++) {
            float x, y, h;
            for (int j = 0; j < app->tidal->max2; j++) {
                if (app->tidal->noteMatrix[i][j] == 1) {
                    x = ofMap(j, 0, app->tidal->max2, 0, width);
                    h = height / (app->tidal->instNumMax);
                    float y = h * i;
                    ofSetColor(255);
                    ofDrawRectangle(x, y, width/app->tidal->resolution/12.0, h);
                }
            }
            ofDrawBitmapStringHighlight(instNames[i], 4, height / (app->tidal->instNumMax) * i + 14, ofColor(63));
            if (i > 0) {
                ofSetColor(127);
                ofDrawLine(0, height / (app->tidal->instNumMax) * i, width, height / (app->tidal->instNumMax) * i);
            }
        }
    }
    ofPopMatrix();
    
    //draw graph
    float x, y, gwidth, gheight, graphX;
    float graphWidth;
    x = 20;
    y = ofGetHeight()/2 + 20;
    graphX = 70;
    gwidth = ofGetWidth() - 40 - graphX;
    gheight = 10;
    
    ofTranslate(x, y);
    ofPushMatrix();
    ofSetColor(255);
    ofDrawBitmapString("Syncopation Degree", 0, 0);
    ofTranslate(0, -8);
    for (int i = 0; i < app->tidal->instNumMax; i++) {
        ofTranslate(0, 14);
        graphWidth = ofMap(app->tidal->syncopation[i], 0, 20, 0, gwidth);
        ofSetColor(63);
        ofDrawRectangle(graphX, 0, gwidth, gheight);
        ofSetColor(63, 127, 255);
        ofDrawRectangle(graphX, 0, graphWidth, gheight);
        ofSetColor(255);
        //ofDrawBitmapString("S"
        //                   + ofToString(i) + ":"
        //                   + ofToString(app->tidal->syncopation[i]), 0, 12);
        ofDrawBitmapString(instNames[i], 0, 10);
        ofDrawBitmapString(ofToString(app->tidal->syncopation[i]), graphX + 5, 10);
    }
    ofTranslate(0, 40);
    ofDrawBitmapString("Entropy", 0, 0);
    ofTranslate(0, -8);
    for (int i = 0; i < app->tidal->instNumMax; i++) {
        ofTranslate(0, 14);
        graphWidth = ofMap(powf(app->tidal->entropy[i], 10), 0, 1, 0, gwidth);
        ofSetColor(63);
        ofDrawRectangle(graphX, 0, gwidth, gheight);
        ofSetColor(63, 127, 255);
        ofDrawRectangle(graphX, 0, graphWidth, gheight);
        ofSetColor(255);
        //ofDrawBitmapString("E"
        //                   + ofToString(i) + ":"
        //                   + ofToString(app->tidal->entropy[i], 2), 0, 10);
        ofDrawBitmapString(instNames[i], 0, 10);
        ofDrawBitmapString(ofToString(app->tidal->entropy[i]), graphX + 5, 10);
    }
    ofPopMatrix();
}

void StSyncopationMonitor::drawGrid(){
    ofSetColor(94);
    for (int i = 0; i < 32; i++) {
        float x = ofMap(i, 0, 32, 0, width);
        ofDrawLine(x, 0, x, height);
    }
    ofSetColor(191);
    for (int i = 0; i < 8; i++) {
        float x = ofMap(i, 0, 8, 0, width);
        ofDrawLine(x, 0, x, height);
    }
    ofSetColor(220);
    ofNoFill();
    ofDrawRectangle(0, 0, width, height);
    ofFill();
}

void StSyncopationMonitor::stateExit(){
    
}

void StSyncopationMonitor::stateEnter(){
    
}

string StSyncopationMonitor::getName(){
    return name;
}
