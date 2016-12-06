#pragma once
#include "ofMain.h"

class TidalPulse {
public:
    TidalPulse(float span);
    void draw();
    
    float span;
    float time;
    int instNum;
    int totalNum;
    ofColor col;
};
