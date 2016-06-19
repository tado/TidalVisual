#include "StISFSerching.hpp"

void StISFSerching::setup(){
    name = "StISFSerching";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/SearchingForSomething.fs");
}

void StISFSerching::update(){
    isf->setUniform<float>("modVal", ofMap(app->p1, 0.0, 1.0, 0.1, 0.5));
    isf->setUniform<float>("zAdder", ofMap(app->p2, 0.0, 1.0, 0.0, 1.0));
    isf->update();
}

void StISFSerching::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFSerching::stateExit(){
    
}

void StISFSerching::stateEnter(){

}

string StISFSerching::getName(){
    return name;
}