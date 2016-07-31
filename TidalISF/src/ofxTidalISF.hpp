#pragma once
#include "ofMain.h"
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

class ofxTidalISF {
public:
    ofxTidalISF(int layer);
    void update();
    void draw();
    
    //ISFDirt
    string currentISF;
    vector<ISFDirt *> isfDirts;
    int layer;
    float gain;
    
    //IO
    CustomPathFilter pathFilter;
};