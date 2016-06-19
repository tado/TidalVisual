#include "StISFLightTunnel.hpp"

void StISFLightTunnel::setup(){
    name = "StISFLightTunnel";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/LightTunnel.fs");
}

void StISFLightTunnel::update(){
    isf->setUniform<float>("shifth", ofMap(app->p1, 0, 1, -0.8, 0.8));
    isf->setUniform<float>("shiftv", ofMap(app->p2, 0, 1, -0.8, 0.8));
    isf->update();
}

void StISFLightTunnel::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFLightTunnel::stateExit(){
    
}

void StISFLightTunnel::stateEnter(){

}

string StISFLightTunnel::getName(){
    return name;
}