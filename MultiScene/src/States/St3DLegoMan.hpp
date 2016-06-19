#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"
#include "ofxAssimpModelLoader.h"

class St3DLegoMan : public itg::ofxState<SharedData> {
public:
    virtual void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    
    ofEasyCam cam;
    ofVec3f camrot;
    ofLight light;
    
    ofxAssimpModelLoader model;
    
};