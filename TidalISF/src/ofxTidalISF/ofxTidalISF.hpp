#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxThreadedOSCReceiver.h"
#include "ISFLayer.hpp"
#include "ofxPostProcessing.h"

class ofxTidalISF {
public:
    ofxTidalISF(int port);
    void update();
    void draw();
    void oscReceiveEvent(ofxOscMessage &m);
    void restPostProcess();
    
    int port;
    ofxThreadedOSCReceiver receiver;
    vector<ISFLayer *> isfLayers;
    static const int layerNum = 4;
    
    vector<string> intArgs;
    vector<string> floatArgs;
    
    //postprocess
    ofxPostProcessing post;
    BloomPass::Ptr bloom;
    KaleidoscopePass::Ptr kaleido;
    NoiseWarpPass::Ptr noise;
    RGBShiftPass::Ptr rgb;
    LimbDarkeningPass::Ptr darken;
    EdgePass::Ptr edge;
    PixelatePass::Ptr pixel;
    ContrastPass::Ptr contrast;
    ConvolutionPass::Ptr conv;
    DofPass::Ptr dof;
    FakeSSSPass::Ptr sss;
    FxaaPass::Ptr fxaa;
    VerticalTiltShifPass::Ptr vtilt;
    HorizontalTiltShifPass::Ptr htilt;
    GodRaysPass::Ptr god;
    BleachBypassPass::Ptr bleach;
    LUTPass::Ptr lut;
    ToonPass::Ptr toon;
};
