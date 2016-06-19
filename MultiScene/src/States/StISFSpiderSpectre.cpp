#include "StISFSpiderSpectre.hpp"

void StISFSpiderSpectre::setup(){
    name = "StISFSpiderSpectre";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/SpiderSpectre.fs");
}

void StISFSpiderSpectre::update(){
    isf->setUniform<float>("mouseX", ofMap(app->p1, 0.0, 1.0, -2.0, 2.0));
    isf->setUniform<float>("mouseY", ofMap(app->p2, 0.0, 1.0, -2.0, 2.0));
    isf->update();
}

void StISFSpiderSpectre::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFSpiderSpectre::stateExit(){
    
}

void StISFSpiderSpectre::stateEnter(){
    
}

string StISFSpiderSpectre::getName(){
    return name;
}