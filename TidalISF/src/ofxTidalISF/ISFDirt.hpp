#pragma once
#include "ofMain.h"
#include "ofxISF.h"

class ISFDirt {
public:
    ISFDirt(string name);
    void setup();
    void update();
    void draw();
    
    string name;
    ofxISF::Shader *isf;
};