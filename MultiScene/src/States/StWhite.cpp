#include "StWhite.hpp"

void StWhite::setup(){
    name = "StWhite";
    app = ((ofApp*)ofGetAppPtr());
}

void StWhite::update(){
    /*
     cout << "params : "
     << app->p1 << ", "
     << app->p2 << ", "
     << app->p3 << endl;
     */
}

void StWhite::draw(){
    float alpha = ofMap(app->p1, 0, 1, 0, 255);
    ofSetColor(255, 255, 255, alpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

void StWhite::stateExit(){
    
}

void StWhite::stateEnter(){
    
}

string StWhite::getName(){
    return name;
}