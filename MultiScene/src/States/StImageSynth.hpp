#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"
#include "ImageSynth.h"

class StImageSynth : public itg::ofxState<SharedData> {
public:
    virtual void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    
    vector<ImageSynth*> imageSynths;
    float zscale;
    ofEasyCam cam;
    ofVec3f camrot;
};