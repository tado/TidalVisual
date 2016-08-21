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
        string name = m.getArgAsString(0);
        int l = m.getArgAsInt(3);
        isfLayers[l]->currentISF = name;
        isfLayers[l]->gain = m.getArgAsFloat(2);
        for (int i = 0; i < isfLayers[l]->isfDirts.size(); i++) {
            isfLayers[l]->isfDirts[i]->isf->setUniform<float>("vel", m.getArgAsFloat(1));
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