#include "ofxTidalISF.hpp"

ofxTidalISF::ofxTidalISF(int _port){
    port = _port;
    for (int i = 0; i < layerNum; i++) {
        ISFLayer *ti = new ISFLayer(i);
        isfLayers.push_back(ti);
    }
    
    //OSC
    receiver.setup(port);
    ofAddListener(receiver.messageReceived, this, &ofxTidalISF::oscReceiveEvent);
    receiver.start();
}

void ofxTidalISF::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/ofplay"){
        int l = 0;
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
            if (argName == "l") {
                l = m.getArgAsInt(i+1);
            }
            if (argName == "s") {
                isfLayers[l]->currentISF = m.getArgAsString(i+1);
            }
            if (argName == "vel"
                || argName == "x"
                || argName == "y"
                || argName == "radius"
                || argName == "smooth"
                || argName == "r"
                || argName == "g"
                || argName == "b"
                || argName == "a"
                ) {
                float argValue = m.getArgAsFloat(i+1);
                for(int j = 0; j < isfLayers[l]->isfDirts.size(); j++){
                    if(isfLayers[l]->isfDirts[j]->name == isfLayers[l]->currentISF){
                        isfLayers[l]->isfDirts[j]->isf->setUniform<float>(argName, argValue);
                    }
                }
                //cout << "argName = " << argName << ", argValue = " << argValue << endl;
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
