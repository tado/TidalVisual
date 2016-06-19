#include "StImageSynth.hpp"

void StImageSynth::setup(){
    name = "StImageSynth";
    app = ((ofApp*)ofGetAppPtr());
    zscale = 0.0;
    camrot = ofVec3f(0, 0, 0);
    cam.setFov(100);
    cam.setDistance(ofGetHeight()/1.5);
    
    //init images
    float size = 500;
    for (int i = 0; i < 4 ; i++) {
        ofImage image;
        string imgStr = "img/image" + ofToString(i) + ".jpg";
        image.load(imgStr);
        ofVec3f pos = ofVec3f(ofRandom(-size, size), ofRandom(-size, size), ofRandom(-size, size));
        ImageSynth *s = new ImageSynth(image, pos);
        s->zscale = zscale;
        s->rotSpeed = ofVec3f(ofRandom(-0.2, 0.2), ofRandom(-0.2, 0.2), ofRandom(-0.2, 0.2));
        imageSynths.push_back(s);
    }
}

void StImageSynth::update(){
    zscale = ofMap(app->p1, 0, 1, 0, 5);
    camrot.x = ofMap(app->p2, 0, 1, 0, 180);
    camrot.y = ofMap(app->p3, 0, 1, 0, 180);
    // update meshes
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->zscale = zscale;
        imageSynths[i]->update();
    }
}

void StImageSynth::draw(){
    app->post[0]->setEnabled(true);
    app->post.begin();
    ofBackground(0, 0, 0);
    ofSetColor(255);
    ofEnableDepthTest();
    cam.begin();
    ofRotateX(camrot.x);
    ofRotateY(camrot.y);
    ofRotateZ(camrot.z);
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->draw();
    }
    cam.end();
    ofDisableDepthTest();
    app->post.end();
}

void StImageSynth::stateExit(){
    
}

void StImageSynth::stateEnter(){

}

string StImageSynth::getName(){
    return name;
}