#include "TidalPulse.hpp"

TidalPulse::TidalPulse(float _span){
    span = _span;
}

void TidalPulse::draw(){
    ofDrawLine(time*span, ofGetHeight()/totalNum*instNum,
    time*span, ofGetHeight()/totalNum*(instNum+1));
}
