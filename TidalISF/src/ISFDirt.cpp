#include "ISFDirt.hpp"

ISFDirt::ISFDirt(string _name){
    isf = new ofxISF::Shader();
    isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
    isf->load("ISF/" + _name + ".fs");
    name = _name;
}

void ISFDirt::setup(){
    
}

void ISFDirt::update(){
    if (name.length() > 0) {
        isf->update();
    }
}

void ISFDirt::draw(){
    if (name.length() > 0) {
        ofSetColor(255);
        isf->draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}