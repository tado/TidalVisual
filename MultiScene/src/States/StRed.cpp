#include "StRed.hpp"

void StRed::setup(){
    name = "StRed";
    app = ((ofApp*)ofGetAppPtr());
}

void StRed::update(){
    /*
    cout << "params : "
    << app->p1 << ", "
    << app->p2 << ", "
    << app->p3 << endl;
     */
}

void StRed::draw(){
    float alpha = ofMap(app->p1, 0, 1, 0, 255);
    ofSetColor(255, 0, 0, alpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

void StRed::stateExit(){
    
}

void StRed::stateEnter(){
    
}

string StRed::getName(){
    return name;
}