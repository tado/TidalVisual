#include "StISFRGBRipple.hpp"

void StISFRGBRipple::setup(){
    name = "StISFRGBRipple";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/RGBRipple.fs");
}

void StISFRGBRipple::update(){
    isf->setUniform<float>("rippleSpeed", ofMap(app->p1, 0, 1, 1, 2));
    isf->update();
}

void StISFRGBRipple::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFRGBRipple::stateExit(){
    
}

void StISFRGBRipple::stateEnter(){

}

string StISFRGBRipple::getName(){
    return name;
}