#include "StISFTopologica.hpp"

void StISFTopologica::setup(){
    name = "StISFTopologica";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/Topologica.fs");
}

void StISFTopologica::update(){
    isf->setUniform<float>("noiseVal", app->p1);
    isf->setUniform<float>("mouseY", app->p2);
    isf->update();
}

void StISFTopologica::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFTopologica::stateExit(){
    
}

void StISFTopologica::stateEnter(){

}

string StISFTopologica::getName(){
    return name;
}