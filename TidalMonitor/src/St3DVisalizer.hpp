#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"
#include "ofVbo.h"

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
    void billboardBegin();
    void billboardEnd();
    
    string name;
    ofApp *app;
    float top;
    float left;
    float width;
    float height;
    ofEasyCam cam;
    vector<instPath> path;

    // billboard particles
    static const int NUM_BILLBOARDS  = 128;
    float billboardSizeTarget[NUM_BILLBOARDS];
    ofVec3f currentLoc[NUM_BILLBOARDS];
    ofVec3f loc[NUM_BILLBOARDS];
    ofShader billboardShader;
    ofImage texture;
    ofVboMesh billboards;
};
