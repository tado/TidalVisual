#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"
#include "ISFLayer.hpp"

class ofxTidalISF {
public:
    ofxTidalISF(int port);
    void update();
    void draw();
    void oscReceiveEvent(ofxOscMessage &m);
    
    //OSC
    //ofxOscReceiver receiver;
    int port;
    ofxThreadedOSCReceiver receiver;
    
    vector<ISFLayer *> isfLayers;
    
    static const int layerNum = 4;
};