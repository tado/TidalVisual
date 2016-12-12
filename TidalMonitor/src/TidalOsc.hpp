#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"

/*
class TidalNote {
public:
    int instNum;
    float beatCount;
};
*/

class TidalOsc {
public:
    TidalOsc(int port);
    void oscReceiveEvent(ofxOscMessage &m);
    void calcStat();
    void showLog();

    string inst;    
    int lastSyncTime;
    int syncTime;
    int syncCount;
    int syncLength;
    float resolution;
    vector<float> cycleBeatCounts;
    int cycleNoteNum;
    vector<string> instNames;
    
    ofxThreadedOSCReceiver receiver;
    //vector<TidalNote> notes;
    
    int noteCount;
    int totalNoteCount;
    float syncopationScore;
};
