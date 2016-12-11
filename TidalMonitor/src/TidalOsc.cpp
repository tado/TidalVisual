#include "TidalOsc.hpp"
#include "ofApp.h"

TidalOsc::TidalOsc(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &TidalOsc::oscReceiveEvent);
    receiver.start();
    lastSyncTime = 0;
    syncCount = 0;
    resolution = 1024.0;
    inst = "";
    
    noteCount = 0;
    totalNoteCount = 0;
}

void TidalOsc::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/play2"){
        //get inst name
        for (int i = 0; i < m.getNumArgs(); i++) {
            if(m.getArgAsString(i) == "s"){
                inst = m.getArgAsString(i+1);
            }
        }
        if (inst != "sync") {
            //calculate beat count
            TidalNote n;
            n.beatCount = (syncCount * 4) + round((ofGetElapsedTimeMillis() - syncTime) * (resolution * 4.0) / float(syncLength)) / resolution;
            if(n.beatCount > 32){
                n.beatCount -= 32;
            }
            
            //generate inst name list
            vector<string>::iterator iter = find(instNames.begin(), instNames.end(), inst);
            size_t index = std::distance(instNames.begin(), iter);
            if(index == instNames.size()){
                instNames.push_back(inst);
            }
            
            //set inst num
            for (int i = 0; i < instNames.size(); i++) {
                if (inst == instNames[i]){
                    n.instNum = i;
                    break;
                }
            }
            notes.push_back(n);
            noteCount++;
        } else {
            syncCount++;
            syncCount = syncCount % 8;
            
            //clear notes and inst names
            if (syncCount == 0) {
                //calculate note stats
                calcStat();
                
                notes.clear();
                instNames.clear();
            }
            //calc sync length
            syncTime = ofGetElapsedTimeMillis();
            syncLength = syncTime - lastSyncTime;
            lastSyncTime = syncTime;

        }
    }
}

void TidalOsc::calcStat(){
    float syncopation[] = {0, 3, 2, 3, 1, 3, 2, 3};
    totalNoteCount = noteCount / 8;
    noteCount = 0;
    syncopationScore = 0;
    int currentSyncopation = 0;
    int score;
    for (int i = 0; i < notes.size(); i++) {
        score =  int(round(round(notes[i].beatCount * 8) / 4.0)) % 8;
        currentSyncopation += syncopation[score];
    }
    syncopationScore = currentSyncopation / float(notes.size());
}

void TidalOsc::showLog(){
    /*
    cout << "inst names = ";
    for (int i = 0; i < instNames.size(); i++) {
        cout << instNames[i] << ", ";
    }
    cout << endl;
    */
    cout << "nots = ";
    for (int i = 0; i < notes.size(); i++) {
        cout << notes[i].beatCount << ", ";
    }
    cout << endl;
    
    cout << "inst: " << inst
    //<< ", inst num : " << instNum
    << ", time : " << ofGetElapsedTimeMillis()
    << ", beat : " << ofGetElapsedTimeMillis() - syncTime
    << ", sync length : " << syncLength
    << ", sync count : " << syncCount
    //<< ", beat count : " << beatCount
    << endl;
}
