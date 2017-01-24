#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"

class instPath {
public:
    vector<ofVec3f> locs;
};

class St3DVisalizer : public itg::ofxState<SharedData> {
public:
    void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    float top;
    float left;
    float width;
    float height;
    ofEasyCam cam;
    ofMesh mesh;
    vector<instPath> path;
    ofVec3f currentLoc[128];
};
