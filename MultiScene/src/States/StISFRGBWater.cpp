#include "StISFRGBWater.hpp"

void StISFRGBWater::setup(){
    name = "StISFRGBWater";
    app = ((ofApp*)ofGetAppPtr());
    
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/RGB Water.fs");
}

void StISFRGBWater::update(){
    isf->setUniform<float>("distort", ofMap(app->p1, 0, 1, 1, 2));
    isf->update();
}

void StISFRGBWater::draw(){
    app->post.begin();
    ofSetColor(255);
    isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    app->post.end();
}

void StISFRGBWater::stateExit(){
    
}

void StISFRGBWater::stateEnter(){

}

string StISFRGBWater::getName(){
    return name;
}