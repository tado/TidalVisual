#include "StBoxes.hpp"

void StBoxes::setup(){
    name = "StBoxes";
    app = ((ofApp*)ofGetAppPtr());

    boxsize = ofGetHeight()/40;
    numX = ofGetWidth() / boxsize;
    numY = ofGetHeight() / boxsize;
    num = numX * numY;
    ofVec3f loc;
    for (int i = 0; i < num; i++) {
        loc.x = 0;
        loc.y = 0;
        loc.z = ofRandom(-1.0, 1.0);
        boxLoc.push_back(loc);
    }
    cam.setFov(100);
    cam.setDistance(ofGetHeight()/4);
}

void StBoxes::update(){
    strength = ofMap(app->p1, 0, 1, 0, boxsize * 12.0);
    /*
    if (ofGetFrameNum() % 10 == 0) {
        boxLoc.clear();
        ofVec3f loc;
        for (int i = 0; i < num; i++) {
            loc.x = 0;
            loc.y = 0;
            loc.z = ofRandom(-1.0, 1.0);
            boxLoc.push_back(loc);
        }
    }
     */
}

void StBoxes::draw(){
    app->post[0]->setEnabled(true);
    //app->post[8]->setEnabled(true);
    app->post.begin();
    cam.begin();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    //light.enable();
    ofBackground(0, 0, 0);
    ofSetColor(100);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetLineWidth(3.0);
    ofNoFill();
    //ofEnableDepthTest();
    for (int j = 0; j < numY; j++) {
        for (int i = 0; i < numX; i++) {
            ofPushMatrix();
            ofTranslate(boxsize * i, boxsize * j, boxLoc[i * j].z * strength);
            ofDrawBox(boxsize * 1.0);
            ofPopMatrix();
        }
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetLineWidth(1.0);
    ofFill();
    //ofDisableDepthTest();
    //light.disable();
    cam.end();
    app->post.end();
}

void StBoxes::stateExit(){
    //ofDisableLighting();
    app->post[0]->setEnabled(false);
}

void StBoxes::stateEnter(){
    //ofEnableLighting();
    light.setSpotlight();
    light.setPosition(-ofGetWidth(), -ofGetHeight(), 1000);
    light.lookAt(ofVec3f(0, 0, 0));
    light.setAmbientColor(ofFloatColor(0.0));
    light.setDiffuseColor(ofFloatColor(0.6));
    light.setSpecularColor(ofFloatColor(0.0));
    app->post[0]->setEnabled(true);
}

string StBoxes::getName(){
    return name;
}