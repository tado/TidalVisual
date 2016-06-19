#include "StBoxRotation.hpp"

void StBoxRotation::setup(){
    name = "StBoxRotation";
    app = ((ofApp*)ofGetAppPtr());
    
    boxsize = ofGetHeight()/40;
    numX = ofGetWidth() / boxsize;
    numY = ofGetHeight() / boxsize;
    num = numX * numY;
    ofVec3f rot;
    for (int i = 0; i < num; i++) {
        rot.x = ofRandom(-90, 90);
        rot.y = ofRandom(-90, 90);
        rot.z = ofRandom(10, 40);
        boxRot.push_back(rot);
    }
    cam.setFov(100);
    cam.setDistance(ofGetHeight()/4);
}

void StBoxRotation::update(){
    strength = ofMap(app->p1, 0, 1, 0, 1.0);
    
    /*
    if (ofGetFrameNum() % 10 == 0) {
        boxRot.clear();
        ofVec3f rot;
        for (int i = 0; i < num; i++) {
            rot.x = ofRandom(-10, 10);
            rot.y = ofRandom(-10, 10);
            rot.z = ofRandom(-10, 10);
            boxRot.push_back(rot);
        }
    }
     */
}

void StBoxRotation::draw(){
    app->post[0]->setEnabled(true);
    //app->post[8]->setEnabled(true);
    app->post.begin();
    cam.begin();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    //light.enable();
    ofBackground(0, 0, 0);
    ofSetColor(140);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //ofEnableDepthTest();
    ofSetLineWidth(3.0);
    ofNoFill();
    for (int j = 0; j < numY; j++) {
        for (int i = 0; i < numX; i++) {
            ofPushMatrix();
            ofTranslate(boxsize * i, boxsize * j, 0);
            //ofRotateX(boxRot[i * j].x * strength);
            //ofRotateY(boxRot[i * j].y * strength);
            ofRotateZ(boxRot[i * j].z * strength);
            //ofDrawBox(boxsize * 0.9);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofDrawRectangle(0, 0, boxsize * 1.5, boxsize * 1.5);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopMatrix();
        }
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofFill();
    ofSetLineWidth(1.0);
    //ofDisableDepthTest();
    //light.disable();
    cam.end();
    app->post.end();
}

void StBoxRotation::stateExit(){
    //ofDisableLighting();
    app->post[0]->setEnabled(false);
}

void StBoxRotation::stateEnter(){
    //ofEnableLighting();
    light.setSpotlight();
    light.setPosition(-ofGetWidth(), -ofGetHeight(), 1000);
    light.lookAt(ofVec3f(0, 0, 0));
    light.setAmbientColor(ofFloatColor(0.0));
    light.setDiffuseColor(ofFloatColor(0.6));
    light.setSpecularColor(ofFloatColor(0.1));
    app->post[0]->setEnabled(true);
}

string StBoxRotation::getName(){
    return name;
}