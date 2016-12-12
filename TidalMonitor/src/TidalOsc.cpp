#include "TidalOsc.hpp"
#include "ofApp.h"

TidalOsc::TidalOsc(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &TidalOsc::oscReceiveEvent);
    receiver.start();
    lastSyncTime = 0;
    syncCount = 0;
    resolution = 128.0;
    inst = "";
    
    noteCount = 0;
    totalNoteCount = 0;
}

void TidalOsc::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/n_go"){
        //calculate beat count
        TidalNote n;
        int beatCount =  round((ofGetElapsedTimeMillis() - syncTime) / float(syncLength) * 32.0);
        n.beatCount = beatCount + syncCount * 32;
        
        cycleBeatCounts.push_back(beatCount % 32);
        cycleNoteNum++;
        
        //generate inst name list
        vector<string>::iterator iter = find(instNames.begin(), instNames.end(), inst);
        size_t index = std::distance(instNames.begin(), iter);
        if(index == instNames.size()){
            instNames.push_back(inst);
        }
        /*
        //set inst num
        for (int i = 0; i < instNames.size(); i++) {
            if (inst == instNames[i]){
                n.instNum = i;
                break;
            }
        }
        */
        n.instNum = 0;
        //notes.push_back(n);
        noteCount++;
    }

    if(m.getAddress() == "/play2"){
        //get inst name
        for (int i = 0; i < m.getNumArgs(); i++) {
            if(m.getArgAsString(i) == "s"){
                inst = m.getArgAsString(i+1);
            }
        }
        if (inst == "sync") {
            syncCount++;
            syncCount = syncCount % 8;
            
            //calculate note stats
            calcStat();
            
            //clear notes and inst names
            if (syncCount % 8 == 0) {
                //notes.clear();
                instNames.clear();
            }
            
            //calc sync length
            syncTime = ofGetElapsedTimeMillis();
            syncLength = syncTime - lastSyncTime;
            lastSyncTime = syncTime;
        } else {
            /*
            //calculate beat count
            TidalNote n;
            int beatCount =  round((ofGetElapsedTimeMillis() - syncTime) / float(syncLength) * 16.0);

            if(cycleBeatCounts.size() > 0){
                if (cycleBeatCounts[cycleBeatCounts.size()-1] == beatCount) {
                    beatCount++;
                }
            }
            
            n.beatCount = beatCount + syncCount * 16;
            
            cycleBeatCounts.push_back(beatCount % 16);
            cycleNoteNum++;
            
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
            showLog();
            */
        }
    }
}

void TidalOsc::calcStat(){
    float syncopation[] = {5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1};
    totalNoteCount = noteCount;
    noteCount = 0;
    syncopationScore = 0;
    int currentSyncopation = 0;
    int score;
    for (int i = 0; i < cycleBeatCounts.size(); i++) {
        //cout << cycleBeatCounts[i] << ", ";
        score =  cycleBeatCounts[i];
        currentSyncopation += syncopation[score];
    }
    //cout << endl;
    syncopationScore = currentSyncopation / float(cycleNoteNum);
    cycleBeatCounts.clear();
    cycleNoteNum = 0;
}

void TidalOsc::showLog(){
    /*
     cout << "inst names = ";
     for (int i = 0; i < instNames.size(); i++) {
     cout << instNames[i] << ", ";
     }
     cout << endl;
    
    cout << "notes = ";
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
     << endl;
     */
}
