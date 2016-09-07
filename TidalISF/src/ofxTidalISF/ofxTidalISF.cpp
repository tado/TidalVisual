#include "ofxTidalISF.hpp"

ofxTidalISF::ofxTidalISF(int _port){
    port = _port;
    for (int i = 0; i < layerNum; i++) {
        ISFLayer *il = new ISFLayer(i);
        isfLayers.push_back(il);
    }
    
    //OSC
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidalISF::oscReceiveEvent);
    receiver.start();
    
    //args
    floatArgs.push_back("vel");
    floatArgs.push_back("x");
    floatArgs.push_back("y");
    floatArgs.push_back("radius");
    floatArgs.push_back("smooth");
    floatArgs.push_back("r");
    floatArgs.push_back("g");
    floatArgs.push_back("b");
}

void ofxTidalISF::oscReceiveEvent(ofxOscMessage &m){
    int l = 0;
    if(m.getAddress() == "/ofplay"){
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
            if (argName == "l") {
                l = m.getArgAsInt(i+1);
            }
            if (argName == "s") {
                isfLayers[l]->currentISF = m.getArgAsString(i+1);
            }
            //find argName in floatArgs
            vector<string>::iterator cIter = find(floatArgs.begin(),floatArgs.end() , argName);
            if (cIter != floatArgs.end()) {
                float argValue = m.getArgAsFloat(i+1);
                for(int j = 0; j < isfLayers[l]->isfs.size(); j++){
                    if(isfLayers[l]->isfs[j]->getName() == isfLayers[l]->currentISF){
                        isfLayers[l]->isfs[j]->setUniform<float>(argName, argValue);
                    }
                }
            }
        }
    }
}

void ofxTidalISF::update(){
    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->update();
    }
}

void ofxTidalISF::draw(){
    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->draw();
    }
}
