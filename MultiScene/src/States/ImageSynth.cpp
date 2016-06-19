#include "ImageSynth.h"

ImageSynth::ImageSynth(ofImage image, ofVec3f _pos){
    pressed = false;
    pos = _pos;
    inputImage = image;
    inputImage.resize(1600, 1600);
    
    // modify image
    cv::Mat src_mat, dst_mat;
    src_mat = ofxCv::toCv(inputImage);
    cv::GaussianBlur(src_mat, dst_mat, cv::Size(121,121), 120, 120);
    ofxCv::toOf(dst_mat, depthImage);
    depthImage.update();
    
    // init rotation
    rot = ofVec3f(ofRandom(360), ofRandom(360), ofRandom(360));
    rotSpeed = ofVec3f(ofRandom(-baseSpeed, baseSpeed), ofRandom(-baseSpeed, baseSpeed), ofRandom(-baseSpeed, baseSpeed));
    
    zscale = 0.0;
    zscaleRatio = 0.0;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    createMesh();
}

void ImageSynth::update(){
    sumLevel = 0;
}

void ImageSynth::updateSynth(){

}

void ImageSynth::draw(){
    if (inputImage.getWidth() > 0) {
        ofPushMatrix();
        {
            ofTranslate(pos);
            ofRotateX(rot.x);
            ofRotateY(rot.y);
            ofRotateZ(rot.z);
            rot += rotSpeed;

            ofScale(1.0, 1.0, zscale);
            if (pressed) {
                ofSetColor(255, 12);
            } else {
                ofSetColor(255, 220);
            }
            inputImage.getTexture().bind();
            mesh.draw();
            inputImage.getTexture().unbind();
        }
        ofPopMatrix();
    }
}

void ImageSynth::drawWireframe(){
    if (inputImage.getWidth() > 0) {
        ofPushMatrix();
        {
            ofTranslate(pos);
            ofRotateX(rot.x);
            ofRotateY(rot.y);
            ofRotateZ(rot.z);
            //rot += rotSpeed;
            
            ofScale(1.0, 1.0, zscale);
            ofSetColor(255, 190);
            mesh.drawWireframe();
        }
        ofPopMatrix();
    }
}

ImageSynth::~ImageSynth(){

}

void ImageSynth::createMesh(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    stepSize = 4;
    ySteps = inputImage.getHeight() / stepSize;
    xSteps = inputImage.getWidth() / stepSize;
    for(int y = 0; y < ySteps; y++) {
        for(int x = 0; x < xSteps; x++) {
            mesh.addVertex(ofVec3f(x * stepSize - inputImage.getWidth()/2.0,
                                   y * stepSize - inputImage.getHeight()/2.0,
                                   (depthImage.getColor(x * stepSize, y * stepSize).getBrightness() - 127)));
            mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
        }
    }
    for(int y = 0; y + 1 < ySteps; y++) {
        for(int x = 0; x + 1 < xSteps; x++) {
            int nw = y * xSteps + x;
            int ne = nw + 1;
            int sw = nw + xSteps;
            int se = sw + 1;
            mesh.addIndex(nw);
            mesh.addIndex(ne);
            mesh.addIndex(se);
            mesh.addIndex(nw);
            mesh.addIndex(se);
            mesh.addIndex(sw);
        }
    }
}