#include "ofxTidalDrop.hpp"

ofxTidalDrop::ofxTidalDrop(){
    //OSC
    receiver.setup(3333);
    ofAddListener(receiver.messageReceived, this, &ofxTidalDrop::oscReceiveEvent);
    receiver.start();
    started = false;
    startTime = 0;
    span = ofGetWidth()/4000.0;
    ofSetLogLevel(OF_LOG_SILENT);
    syncCount = 0;
}

void ofxTidalDrop::update(){
    
}

void ofxTidalDrop::draw(){
    ofSetColor(255);
    for (int i = 0; i < pulses.size(); i++) {
        pulses[i]->draw();
    }
    
    //log
    /*
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
     */
}

void ofxTidalDrop::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/play2"){
        //get inst name
        string inst = "";
        for (int i = 0; i < m.getNumArgs(); i++) {
            if(m.getArgAsString(i) == "s"){
                inst = m.getArgAsString(i+1);
            }
        }
        
        if (inst != "sync") {
            //calc currentTime
            float currentTime;
            if (startTime == 0) {
                startTime = ofGetElapsedTimeMillis();
                currentTime = 0;
                //pulses.clear();
                instBuffer.clear();
            } else {
                currentTime = ofGetElapsedTimeMillis() - startTime;
            }
            

            //p->time = currentTime;
            
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
            TidalDrop *p = new TidalDrop();
            p->instNum = instNameFounded;
            p->totalNum = instNames.size();
            p->yPos = 0;
            //push vector
            pulses.push_back(p);
            
            instBuffer.push_back(inst);
        } else {
            syncCount++;
            if (syncCount == 4) {
                startTime = 0;
                syncCount = 0;
            }
            
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
    }
}
