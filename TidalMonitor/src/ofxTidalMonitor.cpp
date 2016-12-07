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
    for (int i = 0; i < instNames.size(); i++) {
        //serch inst name in instNamesBuffer
        vector<string>::iterator iter = find(instNamesBuffer.begin(), instNamesBuffer.end(), instNames[i]);
        size_t index = std::distance(instNamesBuffer.begin(), iter);
        //if not erase it
        if(index == instNamesBuffer.size()){
            instNames.erase(instNames.begin() + i);
        }
    }
    if(instNamesBuffer.size()>instNames.size() * 4){
        instNamesBuffer.erase(instNamesBuffer.begin());
    }
}

void ofxTidalMonitor::draw(){
    ofSetColor(255);
    for (int i = 0; i < pulses.size(); i++) {
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
    cout << "instNamesBuffer : ";
    for (int i = 0; i < instNamesBuffer.size(); i++) {
        cout << instNamesBuffer[i] << ", ";
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

        instNamesBuffer.push_back(inst);
    }
}
