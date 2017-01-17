#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"

class StSyncopationMonitor : public itg::ofxState<SharedData> {
public:
    void setup();
    void update();
    void draw();
    void drawGrid();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    int top;
    int left;
    int width;
    int height;
    
    //int lastCount;
};
