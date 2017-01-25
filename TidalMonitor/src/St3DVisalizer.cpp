#include "St3DVisalizer.hpp"

void St3DVisalizer::setup(){
    name = "St3DVisalizer";
    app = ((ofApp*)ofGetAppPtr());
    top = 20;
    left= 20;
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    for (int i = 0; i < 128; i++) {
        instPath p;
        path.push_back(p);
        currentLoc[i] = ofVec3f(0, 0, 0);
    }
    //billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    billboardShader.load("shadersGL3/Billboard");
    ofDisableArbTex();
    texture.load("particle.png");
    ofEnableAlphaBlending();
    glPointSize(80.0);
}

void St3DVisalizer::update(){
    width = ofGetWidth() - (left * 2);
    height = ofGetHeight()/2 - (top * 2);
    
    billboards.clear();
    
    for (int i = 0; i < app->tidal->instNumMax; i++) {
        loc[i].x = ofMap(app->tidal->syncopation[i], 0, 15, -width/4, width/4);
        loc[i].y = ofMap(app->tidal->entropy[i], 0, 1, -width/4, width/4);
        loc[i].z = ofMap(app->tidal->noteNum[i], 0, 32, -width/4, width/4);
        currentLoc[i] = currentLoc[i] + (loc[i] - currentLoc[i]) * 0.05;
        billboards.addVertex(currentLoc[i]);
        billboards.addColor(ofFloatColor(1.0, 1.0, 1.0));
        if (path[i].locs.size() > 0) {
            if (loc[i] != path[i].locs[path[i].locs.size()-1]) {
                path[i].locs.push_back(loc[i]);
                if (path[i].locs.size() > 16) {
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //ofBackgroundGradient(ofColor(255), ofColor(230, 240, 255));
    cam.begin();
    ofSetLineWidth(2.0);
    //ofEnableDepthTest();
    ofRotateX(30);
    ofRotateY(ofGetElapsedTimef());
    ofSetColor(127);
    ofDrawLine(-width*4, 0, 0, width*4, 0, 0);
    ofDrawLine(0, -width*4, 0, 0, width*4, 0);
    ofDrawLine(0, 0, -width*4, 0, 0, width*4);
    
    ofSetColor(255);
    billboardShader.begin();
    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTexture().bind();
    billboards.draw();
    texture.getTexture().unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    billboardShader.end();
    
    ofSetColor(127);
    for (int i = 0; i < app->tidal->instNumMax; i++) {
        ofNoFill();
        ofBeginShape();
        ofCurveVertices(path[i].locs);
        ofEndShape();
        if (path[i].locs.size() > 1) {
            ofDrawLine(path[i].locs[path[i].locs.size()-2], currentLoc[i]);
        }
        ofFill();
    }
    //ofDisableDepthTest();
    ofSetLineWidth(1.0);
    cam.end();
}

void St3DVisalizer::stateExit(){
    
}

void St3DVisalizer::stateEnter(){
    
}

string St3DVisalizer::getName(){
    return name;
}

void St3DVisalizer::billboardBegin() {
    float modelview[16];
    int i,j;
    glPushMatrix();
    glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
    for( i=0; i<3; i++ ) {
        for( j=0; j<3; j++ ) {
            if ( i==j ) {
                modelview[i*4+j] = 1.0;
            } else {
                modelview[i*4+j] = 0.0;
            }
        }
    }
    glLoadMatrixf(modelview);
}



void St3DVisalizer::billboardEnd() {
    glPopMatrix();
}
