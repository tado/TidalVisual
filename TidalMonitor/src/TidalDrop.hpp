#pragma once
#include "ofMain.h"

class TidalDrop {
public:
    TidalDrop();
    void draw();
    
    float ySpeed;
    float yPos;
    int instNum;
    int totalNum;
    bool notFirst;
    bool syncRect;
};
