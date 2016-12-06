#include "TidalPulse.hpp"

TidalPulse::TidalPulse(float _span){
    span = _span;
}

void TidalPulse::draw(){
    ofDrawLine(time*span, ofGetHeight()/4*instNum, time*span, ofGetHeight()/4*(instNum+1));
}
