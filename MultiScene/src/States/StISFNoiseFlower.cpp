#include "StISFNoiseFlower.hpp"

void StISFNoiseFlower::setup(){
    name = "StISFNoiseFlower";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/NoiseFlower.fs");
}

void StISFNoiseFlower::update(){
    isf->setUniform<float>("zoom", ofMap(app->p1, 0.0, 1.0, 0.1, 1.0));
    isf->update();
}

void StISFNoiseFlower::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFNoiseFlower::stateExit(){
    
}

void StISFNoiseFlower::stateEnter(){

}

string StISFNoiseFlower::getName(){
    return name;
}