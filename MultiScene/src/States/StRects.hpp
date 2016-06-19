#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"

class StRects : public itg::ofxState<SharedData> {
public:
    virtual void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    
    float rectsize;
    int numX, numY;
    int num;
    vector<ofVec3f> rectLoc;
    vector<float> randSize;
    float strength;
    ofEasyCam cam;
    
    ofLight light;
};