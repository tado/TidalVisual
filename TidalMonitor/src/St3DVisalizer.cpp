#include "St3DVisalizer.hpp"

void St3DVisalizer::setup(){
    name = "St3DVisalizer";
    app = ((ofApp*)ofGetAppPtr());
    top = 20;
    left= 20;
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    glPointSize(20.0);
    for (int i = 0; i < 128; i++) {
        instPath p;
        path.push_back(p);
        currentLoc[i] = ofVec3f(0, 0, 0);
    }
    
}

void St3DVisalizer::update(){
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    
    mesh.clear();
    for (int i = 0; i < app->tidal->instNumMax; i++) {
        ofVec3f loc;
        loc.x = ofMap(app->tidal->syncopation[i], 0, 15, -width/4, width/4);
        loc.y = ofMap(app->tidal->entropy[i], 0, 1, -width/4, width/4);
        loc.z = ofMap(app->tidal->noteNum[i], 0, 32, -width/4, width/4);
        currentLoc[i] = currentLoc[i] + (loc - currentLoc[i]) * 0.05;
        mesh.addVertex(currentLoc[i]);
        if (path[i].locs.size() > 0) {
            if (currentLoc[i] != path[i].locs[path[i].locs.size()-1]) {
                path[i].locs.push_back(currentLoc[i]);
                if (path[i].locs.size() > 400) {
                    path[i].locs.erase(path[i].locs.begin());
                }
            }
        } else {
            path[i].locs.push_back(currentLoc[i]);
        }
    }
    for (int i = 0; i < path.size(); i++) {
        if (i > app->tidal->instNumMax) {
            path[i].locs.clear();
        }
    }
}

void St3DVisalizer::draw(){
    cam.begin();
    ofRotateX(30);
    ofRotateY(ofGetElapsedTimef());
    ofSetColor(255, 127);
    ofDrawLine(-width*4, 0, 0, width*4, 0, 0);
    ofDrawLine(0, -width*4, 0, 0, width*4, 0);
    ofDrawLine(0, 0, -width*4, 0, 0, width*4);
    ofSetColor(63, 127, 255);
    mesh.draw();
    ofSetColor(255, 200);
    for (int i = 0; i < app->tidal->instNumMax; i++) {
        ofNoFill();
        ofBeginShape();
        ofVertices(path[i].locs);
        ofEndShape();
        ofFill();
    }
    cam.end();
    ofSetColor(255);
}

void St3DVisalizer::stateExit(){
    
}

void St3DVisalizer::stateEnter(){
    
}

string St3DVisalizer::getName(){
    return name;
}
