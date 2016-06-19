#pragma once

#include "ofMain.h"
#include "ofMain.h"
#include "ofxStateMachine.h"
#include "SharedData.h"
#include "ofxOsc.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
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
    
    itg::ofxStateMachine<SharedData> stateMachine;
    
    //OSC
    ofxOscReceiver receiver;
    static const int PORT = 57120;
    
    //state params
    float p1, p2, p3;
    
    //postprocess
    ofxPostProcessing post;
};
