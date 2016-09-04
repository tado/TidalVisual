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
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
            int l = 0;
            if (argName == "l") {
                int argValue = m.getArgAsInt(i+1);
                l = m.getArgAsInt(i+1);
            }
            if (argName == "vel"
                || argName == "x"
                || argName == "y"
                || argName == "radius"
                || argName == "smooth"
                || argName == "r"
                || argName == "g"
                || argName == "b"
                ) {
                float argValue = m.getArgAsFloat(i+1);
                isfLayers[l]->isfDirts[0]->isf->setUniform<float>(argName, argValue);
                cout << "argName = " << argName << ", argValue = " << argValue << endl;
            }
            if (argName == "s") {
                string argValue = m.getArgAsString(i+1);
                isfLayers[l]->currentISF = argValue;
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
