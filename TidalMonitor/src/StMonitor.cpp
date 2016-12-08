#include "StMonitor.hpp"

void StMonitor::setup(){
    name = "StMonitor";
    app = ((ofApp*)ofGetAppPtr());
}

void StMonitor::update(){

}

void StMonitor::draw(){
    for (int i = 0; i < app->osc->notes.size(); i++) {
        float x = ofMap(app->osc->notes[i].beatCount, 0, 32, 0, ofGetWidth());
        //float y = ofMap(app->osc->notes[i].instNum, 0, app->osc->instNames.size(), 0, ofGetWidth());
        float height = ofGetHeight() / app->osc->instNames.size();
        float y = height * app->osc->notes[i].instNum;
        ofDrawRectangle(x, y, 2, height);
    }
    
}

void StMonitor::stateExit(){

}

void StMonitor::stateEnter(){

}

string StMonitor::getName(){
    return name;
}
