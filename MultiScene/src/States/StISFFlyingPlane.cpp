#include "StISFFlyingPlane.hpp"

void StISFFlyingPlane::setup(){
    name = "StISFFlyingPlane";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/FlyingPlane.fs");
}

void StISFFlyingPlane::update(){
    isf->setUniform<float>("planeBlur", ofMap(app->p1, 0.0, 1.0, 0.5, 1.0));
    isf->update();
}

void StISFFlyingPlane::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFFlyingPlane::stateExit(){
    
}

void StISFFlyingPlane::stateEnter(){
    
}

string StISFFlyingPlane::getName(){
    return name;
}