#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"
#include "TidalPulse.hpp"

class ofxTidalMonitor {
public:
    ofxTidalMonitor();
    void update();
    void draw();
    void oscReceiveEvent(ofxOscMessage &m);

    ofxThreadedOSCReceiver receiver;
    bool started;
    float startTime;
    float preTime;
    vector<TidalPulse *> pulses;
    vector<string> instNames;
    vector<string> instNamesBuffer;
    float span;
};
