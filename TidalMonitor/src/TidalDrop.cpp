#include "TidalDrop.hpp"

TidalDrop::TidalDrop(){
    ySpeed = 5;
    yPos = 0;
    syncRect = false;
}

void TidalDrop::draw(){
    yPos += ySpeed;
    if (syncRect) {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(0, yPos+2, ofGetWidth(), 2);
    } else {
        ofSetColor(255);
        ofDrawRectangle(ofGetWidth()/totalNum*instNum, yPos-5, ofGetWidth()/totalNum-4, 5);
    }
}
