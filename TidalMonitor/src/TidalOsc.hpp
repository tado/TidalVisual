#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"

class TidalNote {
public:
    int instNum;
    float beatCount;
};

class TidalOsc {
public:
    TidalOsc(int port);
    void oscReceiveEvent(ofxOscMessage &m);
    void showLog();

    string inst;
    //int instNum;
    //float beatCount;
    
    int lastSyncTime;
    int syncTime;
    int syncCount;
    int syncLength;
    vector<string> instNames;
    
    ofxThreadedOSCReceiver receiver;
    vector<TidalNote> notes;
};
