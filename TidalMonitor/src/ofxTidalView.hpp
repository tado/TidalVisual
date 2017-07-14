#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"
#include "ofxMIToolBox.h"

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
    void instCleanup();
    void updateCycle();
    
    ofxThreadedOSCReceiver receiver;
    vector<string> instNames;
    vector<string> instBuffer;
    vector<TidalNote> notes;
    
    float cycle;
    float lastCycle;
    int resolution;
    int noteCount;
    bool updated;
    
    static const int max1 = 128;
    static const int max2 = 64;
    int noteMatrix[max1][max2];
    float syncopation[max1];
    double entropy[max1];
    double jointEntropy[max1];
    double mutualInformation[max1];
    int noteNum[max1];
    int instNumMax;
};
