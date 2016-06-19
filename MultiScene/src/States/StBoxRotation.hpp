#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"

class StBoxRotation : public itg::ofxState<SharedData> {
public:
    virtual void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    
    float boxsize;
    int numX, numY;
    int num;
    vector<ofVec3f> boxRot;
    float strength;
    ofEasyCam cam;
    
    ofLight light;
};