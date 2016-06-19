#include "StRects.hpp"

void StRects::setup(){
    name = "StRects";
    app = ((ofApp*)ofGetAppPtr());
    
    rectsize = ofGetHeight()/40;
    numX = ofGetWidth() / rectsize;
    numY = ofGetHeight() / rectsize;
    num = numX * numY;
    cam.setFov(100);
    cam.setDistance(ofGetHeight()/4);
    for (int i = 0; i < num; i++) {
        randSize.push_back(ofRandom(1.0, 4.0));
    }
}

void StRects::update(){
    strength = ofMap(app->p1, 0, 1, 0, rectsize * 2.0);
}

void StRects::draw(){
    app->post[0]->setEnabled(true);
    app->post.begin();
    cam.begin();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    ofBackground(0, 0, 0);
    ofSetColor(100);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetLineWidth(3.0);
    ofNoFill();
    for (int j = 0; j < numY; j++) {
        for (int i = 0; i < numX; i++) {
            ofPushMatrix();
            ofTranslate(rectsize * i, rectsize * j);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofDrawRectangle(0, 0, strength, randSize[i] * strength);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopMatrix();
        }
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetLineWidth(1.0);
    ofFill();
    cam.end();
    app->post.end();
}

void StRects::stateExit(){
    //ofDisableLighting();
    app->post[0]->setEnabled(false);
}

void StRects::stateEnter(){
    app->post[0]->setEnabled(true);
}

string StRects::getName(){
    return name;
}