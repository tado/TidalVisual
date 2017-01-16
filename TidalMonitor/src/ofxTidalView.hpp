#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"

class TidalNote {
public:
    int instNum;
    string instName;
    int beatCount;
    int syncCount;
};


class ofxTidalView {
public:
    ofxTidalView(int port);
    void oscReceiveEvent(ofxOscMessage &m);
    void beatShift();
    void beatMonitor();
    void calcStat();
    
    ofxThreadedOSCReceiver receiver;
    vector<string> instNames;
    vector<string> instBuffer;
    vector<TidalNote> notes;
    
    int lastSyncTime;
    int syncTime;
    //int syncCount;
    int syncLength;
    int resolution;
   
    int noteCount;
    int notePerCycle;
    vector<float> syncopations;
    float syncopationPerCycle;
    
    static const int max1 = 128;
    static const int max2 = 64;
    int noteMatrix[max1][max2];
    int syncopation[max1];
    int instNumMax;
};
