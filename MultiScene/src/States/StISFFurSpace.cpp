#include "StISFFurSpace.hpp"

void StISFFurSpace::setup(){
    name = "StISFFurSpace";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/FurSpace.fs");
}

void StISFFurSpace::update(){
    isf->setUniform<float>("speed", ofMap(app->p1, 0.0, 1.0, 0.1, 2.0));
    isf->setUniform<float>("level", ofMap(app->p2, 0.0, 1.0, 0.01, 0.05));
    isf->update();
}

void StISFFurSpace::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFFurSpace::stateExit(){
    
}

void StISFFurSpace::stateEnter(){
    
}

string StISFFurSpace::getName(){
    return name;
}