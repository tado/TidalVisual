#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void oscReceiveEvent(ofxOscMessage &m);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxThreadedOSCReceiver receiver;
    bool started;
    float startTime;
    float preTime;
    vector<float> currents;
    vector<string> instNames;
    float span;
};
