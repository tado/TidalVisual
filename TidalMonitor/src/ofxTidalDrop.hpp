#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"
#include "TidalDrop.hpp"

class ofxTidalDrop {
public:
    ofxTidalDrop();
    void update();
    void draw();
    void oscReceiveEvent(ofxOscMessage &m);
    
    ofxThreadedOSCReceiver receiver;
    bool started;
    float startTime;
    float preTime;
    vector<TidalDrop *> pulses;
    vector<string> instNames;
    vector<string> instBuffer;
    float span;
    int syncCount;
};
