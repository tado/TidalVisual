#include "StISFRGBSpiral.hpp"

void StISFRGBSpiral::setup(){
    name = "StISFRGBSpiral";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/RGBSpiral.fs");
}

void StISFRGBSpiral::update(){
    isf->setUniform<float>("distort", ofMap(app->p1, 0.0, 1.0, 1.0, 10.0));
    isf->update();
}

void StISFRGBSpiral::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFRGBSpiral::stateExit(){
    
}

void StISFRGBSpiral::stateEnter(){
    
}

string StISFRGBSpiral::getName(){
    return name;
}