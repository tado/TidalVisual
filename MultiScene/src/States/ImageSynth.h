#pragma once
#include "ofMain.h"
#include "ofxCv.h"

class ImageSynth {
public:
    ImageSynth(ofImage image, ofVec3f pos);
    ~ImageSynth();
    void update();
    void updateSynth();
    void draw();
    void drawWireframe();
    void createMesh();
    
    static const int filterSize = 50;
    ofImage inputImage;
    ofImage depthImage;
    ofVec3f pos;
    float startTime;
    ofVec3f rot;
    ofVec3f rotSpeed;
    float sumLevel;
    float zscale;
    float zscaleRatio;
    const float baseSpeed = 0.05;
    
    ofMesh mesh;
    int stepSize, xSteps, ySteps;
    bool pressed;
};