#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"

class TidalNote {
public:
    int instNum;
    string instName;
    float beatCount;
};


class ofxTidalView {
public:
    ofxTidalView(int port);
    void oscReceiveEvent(ofxOscMessage &m);
    void calcStat();
    
    ofxThreadedOSCReceiver receiver;
    vector<string> instNames;
    vector<string> instBuffer;
    vector<TidalNote> notes;
    
    int lastSyncTime;
    int syncTime;
    int syncCount;
    int syncLength;
    int resolution;
   
    int noteCount;
    int notePerCycle;
    vector<float> syncopations;
    float syncopationPerCycle;
};
