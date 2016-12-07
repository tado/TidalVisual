#include "TidalPulse.hpp"

TidalPulse::TidalPulse(float _span){
    span = _span;
    rectWidth = 64;
}

void TidalPulse::draw(){
    /*
    for (int i = 0; i < rectWidth; i++) {
        float alpha = ofMap(i, 0, rectWidth, 100, 0);
        ofSetColor(255, alpha);
        ofDrawRectangle(time*span+i, ofGetHeight()/totalNum*instNum, 0.5, ofGetHeight()/totalNum);
    }
    */
    ofSetColor(255);
    ofDrawRectangle(time*span, ofGetHeight()/totalNum*instNum, 4, ofGetHeight()/totalNum-4);
}
