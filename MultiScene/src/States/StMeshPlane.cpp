#include "StMeshPlane.hpp"

void StMeshPlane::setup(){
    name = "StMeshPlane";
    app = ((ofApp*)ofGetAppPtr());
    
    size = ofGetHeight()/40;
    num = ofGetWidth()/size * ofGetHeight()/size;
    mesh = ofPlanePrimitive(ofGetWidth(), ofGetHeight(), ofGetWidth()/size, ofGetHeight()/size).getMesh();
    ofVec3f loc;
    for (int j = 0; j < ofGetHeight()/size; j++) {
        for (int i = 0; i < ofGetWidth()/size; i++) {
            loc.x = i * size;
            loc.y = j * size;
            loc.z = ofRandom(-1.0, 1.0);
            meshLoc.push_back(loc);
        }
    }
    //img.load("img/image3.jpg");
    //img.resize(1280, 1280);
    cam.setFov(120);
    cam.setDistance(ofGetHeight()/4);
}

void StMeshPlane::update(){
    strength = ofMap(app->p1, 0, 1, 0, 120);
    /*
    if (ofGetFrameNum() % 10 == 0) {
        meshLoc.clear();
        ofVec3f loc;
        for (int j = 0; j < ofGetHeight()/size; j++) {
            for (int i = 0; i < ofGetWidth()/size; i++) {
                loc.x = i * size;
                loc.y = j * size;
                loc.z = ofRandom(-1.0, 1.0);
                meshLoc.push_back(loc);
            }
        }
    }
     */
}

void StMeshPlane::draw(){
    app->post[0]->setEnabled(true);
    //app->post[8]->setEnabled(true);
    app->post.begin();
    cam.begin();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    //light.enable();
    ofBackground(0, 0, 0);
    //ofEnableDepthTest();
    for (int i = 0; i < num; i++) {
        mesh.setVertex(i, ofVec3f(meshLoc[i].x, meshLoc[i].y, meshLoc[i].z * strength));
    }
    //mesh.drawFaces();
    //img.getTexture().bind();
    //ofSetColor(255, 190);
    //mesh.draw();
    ofSetColor(200);
    ofSetLineWidth(2.0);
    mesh.drawWireframe();
    ofSetLineWidth(1.0);
    //img.getTexture().unbind();
    //ofDisableDepthTest();
    //light.disable();

    cam.end();
    app->post.end();
}

void StMeshPlane::stateExit(){
    //ofDisableLighting();
    app->post[0]->setEnabled(false);
}

void StMeshPlane::stateEnter(){
    //ofEnableLighting();
    light.setSpotlight();
    light.setPosition(-ofGetWidth(), -ofGetHeight(), 1000);
    light.lookAt(ofVec3f(0, 0, 0));
    light.setAmbientColor(ofFloatColor(0.0));
    light.setDiffuseColor(ofFloatColor(0.6));
    light.setSpecularColor(ofFloatColor(0.0));
    app->post[0]->setEnabled(true);
}

string StMeshPlane::getName(){
    return name;
}