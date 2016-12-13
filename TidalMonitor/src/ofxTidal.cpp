#include "ofxTidal.hpp"

ofxTidal::ofxTidal(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidal::oscReceiveEvent);
    receiver.start();
    resolution = 16;
    notePerCycle = 0;
    noteCount = 0;
    syncopationPerCycle = 0;
}


void ofxTidal::oscReceiveEvent(ofxOscMessage &m){
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
        }
        if(inst == "sync"){
            syncCount++;
            calcStat();
            if (syncCount == 8) {
                notes.clear();
                instBuffer.clear();
                syncCount = 0;
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
                float syncopation[16] = {5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1};
                syncopations.push_back(syncopation[beatCount]);
                
                //set inst num
                int instNum;
                for (int i = 0; i < instBuffer.size(); i++) {
                    if (instNames[0] == instBuffer[i]){
                        instNum = i;
                        break;
                    }
                }
                
                TidalNote n;
                //n.beatCount = ((syncCount*resolution) + beatCount) % (resolution*8);
                n.beatCount = ((syncCount*resolution) + beatCount);
                n.instNum = instNum;
                notes.push_back(n);
                noteCount++;
            }
            instNames.erase(instNames.begin());
        }
    }
}

void ofxTidal::calcStat(){
    notePerCycle = noteCount;
    noteCount = 0;
    syncopationPerCycle = 0;
    for (int i = 0; i < syncopations.size(); i++) {
        cout << syncopations[i] << ",";
        syncopationPerCycle += syncopations[i];
    }
    cout << endl;
    syncopationPerCycle /= notePerCycle;
    syncopations.clear();
}

