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
    floatArgs.push_back("gain");
    floatArgs.push_back("x");
    floatArgs.push_back("y");
    floatArgs.push_back("radius");
    floatArgs.push_back("smooth");
    floatArgs.push_back("rotSpeed");
    floatArgs.push_back("zoom");
    floatArgs.push_back("r");
    floatArgs.push_back("g");
    floatArgs.push_back("b");
    
    //Postprocessing
    post.init(ofGetWidth(), ofGetHeight());
    bloom = post.createPass<BloomPass>();
    kaleido = post.createPass<KaleidoscopePass>();
    noise = post.createPass<NoiseWarpPass>();
    rgb = post.createPass<RGBShiftPass>();
    edge = post.createPass<EdgePass>();
    pixel = post.createPass<PixelatePass>();
    darken = post.createPass<LimbDarkeningPass>();
    contrast = post.createPass<ContrastPass>();
    conv = post.createPass<ConvolutionPass>();
    dof = post.createPass<DofPass>();
    sss = post.createPass<FakeSSSPass>();
    fxaa = post.createPass<FxaaPass>();
    vtilt = post.createPass<VerticalTiltShifPass>();
    htilt = post.createPass<HorizontalTiltShifPass>();
    god = post.createPass<GodRaysPass>();
    bleach = post.createPass<BleachBypassPass>();
    lut = post.createPass<LUTPass>();
    toon = post.createPass<ToonPass>();
    restPostProcess();
}

void ofxTidalISF::oscReceiveEvent(ofxOscMessage &m){
    //ISF
    if(m.getAddress() == "/ofplay"){
        //get layer num
        int l = 0;
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
            if (argName == "l") {
                l = m.getArgAsInt(i+1);
            }
        }
        //set current inst
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
            if (argName == "s") {
                isfLayers[l]->currentISF = m.getArgAsString(i+1);
            }
        }
        //send params
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
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
    
    //PostProcess
    if(m.getAddress() == "/post"){
        //reset postprocess
        restPostProcess();
        //set postProcess name
        for (int i = 0; i < m.getNumArgs(); i+=2) {
            string argName = m.getArgAsString(i);
            string postName;
            if (argName == "s") {
                postName = m.getArgAsString(i+1);
                if (postName == "bloom") bloom->setEnabled(true);
                if (postName == "kaleido") kaleido->setEnabled(true);
                if (postName == "noise") noise->setEnabled(true);
                if (postName == "rgb") rgb->setEnabled(true);
                if (postName == "edge") edge->setEnabled(true);
                if (postName == "pixel") pixel->setEnabled(true);
                if (postName == "contrast") contrast->setEnabled(true);
                if (postName == "conv") conv->setEnabled(true);
                if (postName == "dof") dof->setEnabled(true);
                if (postName == "sss") sss->setEnabled(true);
                if (postName == "fxaa") fxaa->setEnabled(true);
                if (postName == "vtilt") vtilt->setEnabled(true);
                if (postName == "htilt") htilt->setEnabled(true);
                if (postName == "god") god->setEnabled(true);
                if (postName == "bleach") bleach->setEnabled(true);
                if (postName == "lut") lut->setEnabled(true);
                if (postName == "toon") toon->setEnabled(true);
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
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(0);
    post.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->draw();
    }
    post.end();
}

void ofxTidalISF::restPostProcess(){
    bloom->setEnabled(false);
    kaleido->setEnabled(false);
    noise->setEnabled(false);
    edge->setEnabled(false);
    rgb->setEnabled(false);
    pixel->setEnabled(false);
    contrast->setEnabled(false);
    conv->setEnabled(false);
    dof->setEnabled(false);
    sss->setEnabled(false);
    fxaa->setEnabled(false);
    vtilt->setEnabled(false);
    htilt->setEnabled(false);
    god->setEnabled(false);
    bleach->setEnabled(false);
    lut->setEnabled(false);
    toon->setEnabled(false);
}
