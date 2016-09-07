#pragma once
#include "ofMain.h"
#include "ofxIO.h"
//#include "ISFDIrt.hpp"
#include "ofxISF.h"

// a custom hidden path filter
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

class ISFLayer {
public:
    ISFLayer(int layer);
    void update();
    void draw();
    
    //ISFDirt
    string currentISF;
    vector<ofxISF::Shader *>  isfs;
    int layer;
    float gain;
    
    //IO
    CustomPathFilter pathFilter;
};
