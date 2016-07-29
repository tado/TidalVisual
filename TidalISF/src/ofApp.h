#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"
#include "ofxIO.h"
#include "ISFDIrt.hpp"

// a custom hidden path filter
class CustomPathFilter: public ofxIO::AbstractPathFilter
{
public:
    CustomPathFilter(){
    }
    
    virtual ~CustomPathFilter(){
    }
    
    bool accept(const Poco::Path& path) const {
        // don't return hidden files or files with names containing "FilterMeOut
        return !Poco::File(path).isHidden() &&
        !ofIsStringInString(path.toString(), "FilterMeOut");
    }
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void oscReceiveEvent(ofxOscMessage &m);
    void oscTestEvent(ofxOscMessage &m);
    
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
    
    //OSC
    //ofxOscReceiver receiver;
    static const int PORT = 8000;
    ofxThreadedOSCReceiver receiver;

    //ISFDirt
    string currentISF;
    vector<ISFDirt *> isfDirts;
    
    //IO
    CustomPathFilter pathFilter;
};
