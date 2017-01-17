#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofApp.h"
#include "ofxIO.h"
#include "ofxISF.h"

class CustomPathFilter: public ofxIO::AbstractPathFilter{
public:
    CustomPathFilter(){
    }
    
    virtual ~CustomPathFilter(){
    }
    
    bool accept(const Poco::Path& path) const {
        return !Poco::File(path).isHidden() &&
        !ofIsStringInString(path.toString(), "FilterMeOut");
    }
};

class StISFView : public itg::ofxState<SharedData> {
public:
    void setup();
    void update();
    void draw();
    void stateExit();
    void stateEnter();
    string getName();
    
    string name;
    ofApp *app;
    int top;
    int left;
    int width;
    int height;
    
    //ISFDirt
    //string currentISF;
    int isfNum;
    vector<ofxISF::Shader *>  isfs;
    int lastNum;
    
    //IO
    CustomPathFilter pathFilter;
};
