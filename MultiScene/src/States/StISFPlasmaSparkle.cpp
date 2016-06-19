#include "StISFPlasmaSparkle.hpp"

void StISFPlasmaSparkle::setup(){
    name = "StISFPlasmaSparkle";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/PlasmasSarkle.fs");
}

void StISFPlasmaSparkle::update(){
    isf->setUniform<float>("rotateStrength", ofMap(app->p1, 0.0, 1.0, 0.0, 10.0));
    isf->update();
}

void StISFPlasmaSparkle::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFPlasmaSparkle::stateExit(){
    
}

void StISFPlasmaSparkle::stateEnter(){

}

string StISFPlasmaSparkle::getName(){
    return name;
}