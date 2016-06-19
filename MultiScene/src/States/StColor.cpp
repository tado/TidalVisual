#include "StColor.hpp"

void StColor::setup(){
    name = "StColor";
    app = ((ofApp*)ofGetAppPtr());
}

void StColor::update(){
    /*
     cout << "params : "
     << app->p1 << ", "
     << app->p2 << ", "
     << app->p3 << endl;
     */
}

void StColor::draw(){
    ofColor col;
    col.setHsb(ofRandom(255), 255, 255);
    float alpha = ofMap(app->p1, 0, 1, 0, 255);
    ofSetColor(col, alpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

void StColor::stateExit(){
    
}

void StColor::stateEnter(){
    
}

string StColor::getName(){
    return name;
}