#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"

class StMeshPlane : public itg::ofxState<SharedData> {
public:
    virtual void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    float strength;
    ofEasyCam cam;
    ofMesh mesh;
    vector<ofVec3f> meshLoc;
    int size, num;
    
    ofLight light;
    ofImage img;
};