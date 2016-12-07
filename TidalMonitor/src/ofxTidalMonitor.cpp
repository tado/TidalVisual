#include "ofxTidalMonitor.hpp"

ofxTidalMonitor::ofxTidalMonitor(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //OSC
    receiver.setup(3333);
    ofAddListener(receiver.messageReceived, this, &ofxTidalMonitor::oscReceiveEvent);
    receiver.start();
    started = false;
    startTime = 0;
    span = ofGetWidth()/8000.0;
    ofSetLogLevel(OF_LOG_SILENT);
}

void ofxTidalMonitor::update(){
    /*
     for (int i = 0; i < instNames.size(); i++) {
     //serch inst name in instBuffer
     vector<string>::iterator iter = find(instBuffer.begin(), instBuffer.end(), instNames[i]);
     size_t index = std::distance(instBuffer.begin(), iter);
     //if not erase it
     if(index == instBuffer.size()){
     instNames.erase(instNames.begin() + i);
     }
     }
     if(instBuffer.size()>instNames.size() * 4){
     instBuffer.erase(instBuffer.begin());
     }
     */
    if(instBuffer.size() >= instNames.size()){
        for (int i = 0; i < instNames.size(); i++) {
            //serch inst name in instBuffer
            vector<string>::iterator iter = find(instBuffer.begin(), instBuffer.end(), instNames[i]);
            size_t index = std::distance(instBuffer.begin(), iter);
            //if not erase it
            if(index == instBuffer.size()){
                instNames.erase(instNames.begin() + i);
            }
        }
    }
}

void ofxTidalMonitor::draw(){
    drawGrid();

    ofSetColor(255);
    for (int i = 0; i < pulses.size(); i++) {
        pulses[i]->draw();
        if(pulses[i]->time * pulses[i]->span > (ofGetWidth()-20)){
            pulses.clear();
            startTime = ofGetElapsedTimeMillis();
            instBuffer.clear();
            break;
        }
    }
    
    //log
    cout << "instNames : ";
    for (int i = 0; i < instNames.size(); i++) {
        cout << instNames[i] << ", ";
    }
    cout << endl;
    cout << "instBuffer : ";
    for (int i = 0; i < instBuffer.size(); i++) {
        cout << instBuffer[i] << ", ";
    }
    cout << endl;
}

void ofxTidalMonitor::drawGrid(){
    ofDisableAlphaBlending();
    ofSetColor(60);
    for (int i = 0; i < 64; i++) {
        ofDrawLine(ofGetWidth()/64 * i, 0, ofGetWidth()/64 * i, ofGetHeight());
    }
    ofSetColor(80);
    for (int i = 0; i < 32; i++) {
        ofDrawLine(ofGetWidth()/32 * i, 0, ofGetWidth()/32 * i, ofGetHeight());
    }
    ofSetColor(80, 80, 200);
    for (int i = 0; i < 16; i++) {
        ofDrawLine(ofGetWidth()/16 * i, 0, ofGetWidth()/16 * i, ofGetHeight());
    }
    ofSetColor(220, 80, 80);
    for (int i = 0; i < 8; i++) {
        ofDrawLine(ofGetWidth()/8 * i, 0, ofGetWidth()/8 * i, ofGetHeight());
    }
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
        
        instBuffer.push_back(inst);
    }
}
