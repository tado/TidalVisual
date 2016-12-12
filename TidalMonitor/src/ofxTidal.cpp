#include "ofxTidal.hpp"

ofxTidal::ofxTidal(int port){
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidal::oscReceiveEvent);
    receiver.start();
    resolution = 32;
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
    }

    //que inst
    if(m.getAddress() == "/n_go"){
        if (instNames.size() > 0) {
            if (instNames[0] == "sync") {
                syncCount++;
                syncCount = syncCount % 8;

                syncTime = ofGetElapsedTimeMillis();
                syncLength = syncTime - lastSyncTime;
                lastSyncTime = syncTime;
                
                if (syncCount % 8 == 0) {
                    notes.clear();
                    //instBuffer.clear();
                }
            } else {
                int beatCount =  round((ofGetElapsedTimeMillis() - syncTime) / float(syncLength) * resolution);
                //set inst num
                int instNum;
                for (int i = 0; i < instBuffer.size(); i++) {
                    if (instNames[0] == instBuffer[i]){
                        instNum = i;
                        break;
                    }
                }
                
                TidalNote n;
                n.beatCount = ((syncCount*resolution) + beatCount) % (resolution*8);
                n.instNum = instNum;
                notes.push_back(n);
            }
            instNames.erase(instNames.begin());
        }
    }
}
