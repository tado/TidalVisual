#include "ofxTidalView.hpp"

int weights[16] = {0, -4, -3, -4, -2, -4, -3, -4, -1, -4, -3, -4, -2, -4, -3, -4};
int beats[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

ofxTidalView::ofxTidalView(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidalView::oscReceiveEvent);
    receiver.start();
    resolution = 16;
    notePerCycle = 0;
    noteCount = 0;
    syncopationPerCycle = 0;
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
            //calcStat();
            beatMonitor();
            
            //if (syncCount == 8) {
                notes.clear();
                instBuffer.clear();
                syncCount = 0;
            //}
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
                beats[beatCount] = 1;
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
        noteMatrix[notes[i].instNum][int(notes[i].beatCount) % 16] = 1;
    }
    
    for (int i = 0; i <= instNumMax; i++) {
        cout << "part " << i << " : ";
        for (int j = 0; j < 16; j++) {
            cout << noteMatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void ofxTidalView::calcStat(){
    notePerCycle = noteCount;
    noteCount = 0;
    syncopationPerCycle = 0;
    int grain = 0;
    
    //show log
    for (int i = 0; i < syncopations.size(); i++) {
        cout << syncopations[i] << ",";
    }
    cout << endl;
    
    for (int i = 0; i < 16; i++) {
        cout << beats[i] << ",";
    }
    cout << endl;

    //calcurate grain
    for (int i = 0; i < syncopations.size(); i++) {
        if (grain > syncopations[i]) {
            grain = syncopations[i];
        }
    }
    grain = grain + 1;
    
    cout << "grain : " << grain << endl;

    int skip = 1;
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
    for (int i = 0; i < 16; i += skip) {
        if(beats[i] == 0){
            for (int j = i; j >= 0; j--) {
                j = abs(j % 16);
                if (beats[j] == 1 && weights[i] - weights[j] > 0) {
                    syncopationPerCycle += weights[i] - weights[j % 16];
                    break;
                }
            }
        }
    }
    cout << "syncopation : " << syncopationPerCycle << endl;
    syncopations.clear();
}

