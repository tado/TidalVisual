#include "ofxTidalView.hpp"

int weights[16] = {0, -4, -3, -4, -2, -4, -3, -4, -1, -4, -3, -4, -2, -4, -3, -4};

ofxTidalView::ofxTidalView(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidalView::oscReceiveEvent);
    receiver.start();
    resolution = 16;
    notePerCycle = 0;
    noteCount = 0;
    syncopationPerCycle = 0;
    syncCount = 0;
    for (int i = 0; i < max1; i++) {
        syncopation[i] = 0;
    }
}


void ofxTidalView::oscReceiveEvent(ofxOscMessage &m){
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
            syncCount++;
            beatMonitor();
            calcStat();
            if (syncCount == 4) {
                syncCount = 0;
                instBuffer.clear();
                notes.clear();
            }
        }
    }
    
    //que inst
    if(m.getAddress() == "/n_go"){
        if (instNames.size() > 0) {
            if (instNames[0] == "sync") {
                syncTime = ofGetElapsedTimeMillis();
                syncLength = syncTime - lastSyncTime;
                lastSyncTime = syncTime;
            } else {
                int beatCount =  round((ofGetElapsedTimeMillis() - syncTime) / float(syncLength) * resolution);
                beatCount = beatCount % resolution;
                
                //calc syncopation
                syncopations.push_back(weights[beatCount]);
                
                //set inst num
                int instNum;
                for (int i = 0; i < instBuffer.size(); i++) {
                    if (instNames[0] == instBuffer[i]){
                        instNum = i;
                        break;
                    }
                }
                
                TidalNote n;
                n.beatCount = ((syncCount*resolution) + beatCount);
                n.syncCount = syncCount;
                n.instNum = instNum;
                //n.instName = instNames[instNum];
                notes.push_back(n);
                noteCount++;
            }
            instNames.erase(instNames.begin());
        }
    }
}

void ofxTidalView::beatMonitor(){
    cout << "-------------------------" << endl;
    for (int i = 0; i < max1; i++) {
        for (int j = 0; j < max2; j++) {
            noteMatrix[i][j] = 0;
        }
    }
    instNumMax = 0;
    for (int i = 0; i < notes.size(); i++) {
        if (notes[i].instNum > instNumMax) {
            instNumMax = notes[i].instNum;
        }
    }
    for (int i = 0; i < notes.size(); i++) {
        noteMatrix[notes[i].instNum][int(notes[i].beatCount)] = 1;
    }
    for (int i = 0; i <= instNumMax; i++) {
        cout << "part " << i << " : ";
        for (int j = 0; j < max2; j++) {
            cout << noteMatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void ofxTidalView::calcStat(){
    /*
    //show log
    for (int i = 0; i < syncopations.size(); i++) {
        cout << syncopations[i] << ",";
    }
    cout << endl;
     */
    
    for (int i = 0; i < max1; i++) {
        syncopation[i] = 0;
    }
    
    for (int i = 0; i <= instNumMax; i++) {
        int n[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        int grain = 0;
        int skip = 1;
        for (int j = 0; j < 16; j++) {
            //cout << noteMatrix[i][(syncCount-1) * 16 + j] << ",";
            if (noteMatrix[i][(syncCount-1) * 16 + j] == 1) {
                n[j] = weights[j];
                if (grain > n[j]) {
                    grain = n[j];
                }
            }
            //cout << n[j] << ",";
        }
        //cout << endl;
        grain = grain + 1;
        switch (grain) {
            case -3:
                skip = 1;
                break;
            case -2:
                skip = 2;
                break;
            case -1:
                skip = 4;
                break;
            case 0:
                skip = 8;
                break;
            default:
                skip = 16;
                break;
        }
        
        //calculate syncopation
        for (int j = 0; j < 16; j += skip) {
            if(n[j] == 1){
                for (int k = j; k >= 0; k--) {
                    k = abs(k % 16);
                    if (n[k] <= 0 && weights[j] - weights[k] > 0) {
                        syncopation[i] += weights[j] - weights[k];
                        break;
                    }
                }
            }
        }
        //cout << ", grain : " << grain;
        cout << "syncopation " << i << " : " << syncopation[i] << endl;

    }
}

