#include "ofxTidalMonitor.hpp"

ofxTidalMonitor::ofxTidalMonitor(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //OSC
    receiver.setup(3333);
    ofAddListener(receiver.messageReceived, this, &ofxTidalMonitor::oscReceiveEvent);
    receiver.start();
    started = false;
    startTime = 0;
    span = 0.1;
    ofSetLogLevel(OF_LOG_SILENT);
}

void ofxTidalMonitor::update(){
    bool bufferFound = false;
    for (int i = 0; i < instNames.size(); i++) {
        for (int j = 0; j < instNamesBuffer.size(); j++) {
            if (instNames[i] == instNamesBuffer[j]) {
                bufferFound = true;
            }
        }
        if (bufferFound == false) {
            instNames.erase(instNames.begin() + i);
        }
        bufferFound = false;
    }
}

void ofxTidalMonitor::draw(){
    ofSetColor(255);
    for (int i = 0; i < pulses.size(); i++) {
        // tcout << "Pulse Num = " << i << endl;
        pulses[i]->draw();
        if(pulses[i]->time * pulses[i]->span > ofGetWidth()){
            pulses.clear();
            startTime = ofGetElapsedTimeMillis();
            break;
        }
    }
    
    //log
    cout << "instNames : ";
    for (int i = 0; i < instNames.size(); i++) {
        cout << instNames[i] << ", ";
    }
    cout << endl;
}

void ofxTidalMonitor::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/play2"){
        TidalPulse *p = new TidalPulse(span);
        
        //calc currentTime
        if (startTime == 0) {
            startTime = ofGetElapsedTimeMillis();
        }
        float currentTime = ofGetElapsedTimeMillis() - startTime;
        p->time = currentTime;
        
        //get inst name
        string inst = "";
        for (int i = 0; i < m.getNumArgs(); i++) {
            if(m.getArgAsString(i) == "s"){
                inst = m.getArgAsString(i+1);
            }
        }
        
        //search instname from list
        int instNameFounded = -1;
        for (int i = 0; i < instNames.size(); i++) {
            if(instNames[i] == inst){
                instNameFounded = i;
            }
        }
        if (instNameFounded == -1) {
            instNames.push_back(inst);
            instNameFounded = instNames.size()-1;
        }
        p->instNum = instNameFounded;
        p->totalNum = instNames.size();
        
        //push vector
        pulses.push_back(p);
        
        //set instnameBuffer
        instNamesBuffer.push_back(inst);
        if(instNamesBuffer.size()>instNames.size()*4){
            instNamesBuffer.erase(instNamesBuffer.begin());
        }
    }
}
