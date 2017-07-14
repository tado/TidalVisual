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
    updated = false;
    
    //init arrays
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
        
        //get osc params
        float cps;
        float delta;
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
        
        if (inst == "sync") {
            updateCycle();
        } else {
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
            int beatCount =  int(fractional * resolution);
            
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
        }
        
        
        /*
         } else {
         //sync each one bar
         lastCycle = cycle;
         beatMonitor();
         calcStat();
         instCleanup();
         beatShift();
         notes.clear();
         }
         */
    }
}

void ofxTidalView::updateCycle(){
    lastCycle = cycle;
    beatMonitor();
    calcStat();
    instCleanup();
    beatShift();
    notes.clear();
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
        for (int j = resolution; j < max2 ; j++) {
            noteMatrix[i][j - resolution] = noteMatrix[i][j];
        }
        for (int j = max2-resolution; j < max2 ; j++) {
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
    uint *allVector = (uint *) calloc(resolution,sizeof(uint));
    for (int i = 0; i < instNumMax; i++) {
        for (int j = 0; j < resolution; j++) {
            allVector[j] += uint(noteMatrix[i][max2 - resolution + j]);
            if(allVector[j] > 1) {
                allVector[j] = 1;
            }
        }
    }
    
    for (int i = 0; i < instNumMax; i++) {
        //calculate syncopation
        string bitStr;
        for (int j = 0; j < resolution; j++) {
            bitStr += to_string(noteMatrix[i][max2 - resolution + j]);
        }
        int digit = stoi(bitStr, nullptr, 2);
        syncopation[i] = SG[digit];
        
        cout << "digit " << i << " : "
        << bitStr << " : "  << digit
        << " syncopation : " << SG[digit]
        << endl;
        
        //calc entropy
        uint *currentVector = (uint *) calloc(resolution,sizeof(uint));
        for (int j = 0; j < resolution; j++) {
            currentVector[j] = uint(noteMatrix[i][max2 - resolution + j]);
        }
        entropy[i] = calcEntropy(currentVector, resolution);
        
        //calc note count
        int num = 0;
        for (int j = 0; j < resolution; j++) {
            if (noteMatrix[i][max2 - resolution + j] == 1) {
                num++;
            }
        }
        noteNum[i] = num;
    }
}

