#include "StBlue.hpp"

void StBlue::setup(){
    name = "StBlue";
    app = ((ofApp*)ofGetAppPtr());
}

void StBlue::update(){
    /*
    cout << "params : "
    << app->p1 << ", "
    << app->p2 << ", "
    << app->p3 << endl;
     */
}

void StBlue::draw(){
    float alpha = ofMap(app->p1, 0, 1, 0, 255);
    ofSetColor(0, 0, 255, alpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

void StBlue::stateExit(){
    
}

void StBlue::stateEnter(){
    
}

string StBlue::getName(){
    return name;
}