#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"

class TidalNote {
public:
    int instNum;
    float beatCount;
};


class ofxTidal {
public:
    ofxTidal(int port);
    void oscReceiveEvent(ofxOscMessage &m);
    
    ofxThreadedOSCReceiver receiver;
    vector<string> instNames;
    vector<string> instBuffer;
    vector<TidalNote> notes;
    
    int lastSyncTime;
    int syncTime;
    int syncCount;
    int syncLength;
    
    int resolution;
};
