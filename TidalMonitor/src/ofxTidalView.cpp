#include "ofxTidalView.hpp"
#include "SyncopationData.hpp"
#include<iostream>
#include<bitset>

ofxTidalView::ofxTidalView(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidalView::oscReceiveEvent);
    receiver.start();
    resolution = 16;
    instNumMax = 1;
    noteCount = 0;
    for (int i = 0; i < max1; i++) {
        syncopation[i] = 0;
        entropy[i] = 0;
        noteNum[i] = 0;
        for (int j = 0; j < max2 ; j++) {
            noteMatrix[i][j] = 0;
        }
    }
}

void ofxTidalView::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/play2"){
        float cps;
        float delta;
        float cycle;
        string inst;
        for (int i = 0; i < m.getNumArgs(); i++) {
            if(m.getArgAsString(i) == "cps"){
                cps = m.getArgAsFloat(i+1);
            }
            if(m.getArgAsString(i) == "delta"){
                delta = m.getArgAsFloat(i+1);
            }
            if(m.getArgAsString(i) == "cycle"){
                cycle = m.getArgAsFloat(i+1);
            }
            if(m.getArgAsString(i) == "s"){
                inst = m.getArgAsString(i+1);
            }
        }
        //cout << cps << ", " << delta << ", " << cycle << ", " << inst << endl;
        
        if(inst != "sync"){
            //create unique instname list
            vector<string>::iterator iter = find(instBuffer.begin(), instBuffer.end(), inst);
            size_t index = std::distance(instBuffer.begin(), iter);
            if(index == instBuffer.size()){
                instBuffer.push_back(inst);
            }
            
            //calc beat count
            //int beatCount =  int((cycle - lastCycle) * resolution) % resolution;
            //int beatCount =  int(delta * resolution) % resolution;
            float fractional, integer;
            fractional = modff(cycle, &integer);
            int beatCount =  int(fractional * resolution) % resolution;
            
            //add note to sequence
            int instNum;
            for (int i = 0; i < instBuffer.size(); i++) {
                if (inst == instBuffer[i]){
                    instNum = i;
                    break;
                }
            }
            TidalNote n;
            n.beatCount = beatCount;
            n.instNum = instNum;
            n.instName = inst;
            notes.push_back(n);
            noteCount++;
            
            //add to note matrix
            for (int i = 0; i < notes.size(); i++) {
                noteMatrix[notes[i].instNum][int(notes[i].beatCount) + max2 - resolution] = 1;
            }
        } else {
            //sync each one bar
            lastCycle = cycle;
            beatMonitor();
            calcStat();
            instCleanup();
            beatShift();
            notes.clear();
        }
    }
    
    /*
     //buffer inst name
     string inst;
     if(m.getAddress() == "/play2"){
     //get inst name
     for (int i = 0; i < m.getNumArgs(); i++) {
     if(m.getArgAsString(i) == "s"){
     inst = m.getArgAsString(i+1);
     instNames.push_back(inst);
     }
     }
     //create unique instname list
     vector<string>::iterator iter = find(instBuffer.begin(), instBuffer.end(), inst);
     size_t index = std::distance(instBuffer.begin(), iter);
     if(index == instBuffer.size() && inst != "sync"){
     instBuffer.push_back(inst);
     } else if(inst == "sync"){
     beatMonitor();
     calcStat();
     instCleanup();
     notes.clear();
     beatShift();
     }
     }
     
     //que inst
     if(m.getAddress() == "/n_go"){
     for (int i = 0; i < instNames.size(); i++) {
     if (instNames[i] == "sync") {
     syncTime = ofGetElapsedTimef();
     syncLength = (syncTime - lastSyncTime) / resolution;
     lastSyncTime = syncTime;
     instNames.erase(instNames.begin() + i);
     }
     }
     if (instNames.size() > 0) {
     int beatCount =  round((ofGetElapsedTimef() - syncTime) / syncLength);
     beatCount = beatCount % resolution;
     
     //set inst num
     int instNum;
     string instName;
     for (int i = 0; i < instBuffer.size(); i++) {
     if (instNames[0] == instBuffer[i]){
     instNum = i;
     break;
     }
     }
     TidalNote n;
     n.beatCount = beatCount;
     n.instNum = instNum;
     n.instName = instNames[0];
     notes.push_back(n);
     noteCount++;
     instNames.erase(instNames.begin());
     }
     }
     */
}

void ofxTidalView::instCleanup(){
    vector<int > trackExist;
    for (int i = 0; i < instBuffer.size(); i++) {
        trackExist.push_back(0);
    }
    for (int i = 0; i < instBuffer.size(); i++) {
        for (int j = 0; j < notes.size(); j++) {
            if (notes[j].instNum == i) {
                trackExist[i] = 1;
            }
        }
    }
    for (int i = 0; i < instBuffer.size(); i++) {
        if (trackExist[i] == 0) {
            instBuffer.erase(instBuffer.begin()+i);
            i--;
        }
    }
}

void ofxTidalView::beatShift(){
    for (int i = 0; i < max1; i++) {
        for (int j = 16; j < max2 ; j++) {
            noteMatrix[i][j - 16] = noteMatrix[i][j];
        }
        for (int j = max2-16; j < max2 ; j++) {
            noteMatrix[i][j] = 0;
        }
    }
}

void ofxTidalView::beatMonitor(){
    cout << "-------------------------" << endl;
    instNumMax = instBuffer.size();
    /*
     for (int i = 0; i < notes.size(); i++) {
     noteMatrix[notes[i].instNum][int(notes[i].beatCount) + max2 - resolution] = 1;
     }
     */
    for (int i = 0; i < instNumMax; i++) {
        cout << "part " << i << " : ";
        for (int j = 0; j < max2; j++) {
            cout << noteMatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void ofxTidalView::calcStat(){
    for (int i = 0; i < max1; i++) {
        syncopation[i] = 0.0;
        noteNum[i] = 0.0;
    }
    
    //calclate all part matrix for joint entropy
    uint *allVector = (uint *) calloc(16,sizeof(uint));
    for (int i = 0; i < instNumMax; i++) {
        for (int j = 0; j < 16; j++) {
            allVector[j] += uint(noteMatrix[i][max2 - 16 + j]);
            if(allVector[j] > 1) {
                allVector[j] = 1;
            }
        }
    }
    
    for (int i = 0; i < instNumMax; i++) {
        //calculate syncopation
        string bitStr;
        for (int j = 0; j < 16; j++) {
            bitStr += to_string(noteMatrix[i][max2 - 16 + j]);
        }
        int digit = stoi(bitStr, nullptr, 2);
        cout << "digit " << i << " : " << bitStr << " : "  << digit << endl;
        syncopation[i] = SG[digit];
        
        //calc entropy
        uint *currentVector = (uint *) calloc(16,sizeof(uint));
        for (int j = 0; j < 16; j++) {
            currentVector[j] = uint(noteMatrix[i][max2 - 16 + j]);
        }
        entropy[i] = calcEntropy(currentVector, 16);
    }
}

