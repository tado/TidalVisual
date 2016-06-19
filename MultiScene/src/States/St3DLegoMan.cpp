#include "St3DLegoMan.hpp"

void St3DLegoMan::setup(){
    name = "St3DLegoMan";
    app = ((ofApp*)ofGetAppPtr());
    camrot = ofVec3f(0, 0, 0);
    cam.setFov(100);
    cam.setDistance(ofGetHeight()/8.0);
    
    model.loadModel("obj/lego/LEGO_Man.obj");
    model.setScaleNormalization(true);
    model.setPosition(0, ofGetHeight()/6.0, 0);
    camrot.z = 180;
}

void St3DLegoMan::update(){
    camrot.x += ofMap(app->p1, 0, 1, -30, 30);
    camrot.y += ofMap(app->p2, 0, 1, -30, 30);
    camrot.z += ofMap(app->p3, 0, 1, -30, 30);
}

void St3DLegoMan::draw(){
    app->post[0]->setEnabled(true);
    app->post.begin();
    ofBackground(0, 0, 0);
    ofSetColor(255);
    ofEnableDepthTest();
    cam.begin();
    ofRotateX(camrot.x);
    ofRotateY(camrot.y);
    ofRotateZ(camrot.z);
    light.enable();
    model.drawFaces();
    light.disable();
    cam.end();
    ofDisableDepthTest();
    app->post.end();
}

void St3DLegoMan::stateExit(){
    ofDisableLighting();
    app->post[0]->setEnabled(false);
}

void St3DLegoMan::stateEnter(){
    ofEnableLighting();
    light.setSpotlight();
    light.setPosition(40, 40, 1000);
    light.setAmbientColor(ofFloatColor(0.2, 0.2, 1.0));
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0, 2.0));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    app->post[0]->setEnabled(true);
}

string St3DLegoMan::getName(){
    return name;
}