#include "StBlank.hpp"

void StBlank::setup(){
    name = "StBlank";
    app = ((ofApp*)ofGetAppPtr());
}

void StBlank::update(){
    /*
    cout << "params : "
    << app->p1 << ", "
    << app->p2 << ", "
    << app->p3 << endl;
     */
}

void StBlank::draw(){
    ofBackground(0, 0, 0);
}

void StBlank::stateExit(){
    
}

void StBlank::stateEnter(){
    
}

string StBlank::getName(){
    return name;
}