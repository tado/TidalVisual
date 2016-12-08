#include "StMonitor.hpp"

void StMonitor::setup(){
    name = "StMonitor";
    app = ((ofApp*)ofGetAppPtr());
}

void StMonitor::update(){

}

void StMonitor::draw(){

}

void StMonitor::stateExit(){

}

void StMonitor::stateEnter(){

}

string StMonitor::getName(){
    return name;
}
