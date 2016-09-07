#include "ISFLayer.hpp"

ISFLayer::ISFLayer(int _layer){
    layer = _layer;
    gain = 1.0;
    
    //init ISFs
    std::vector<std::string> files;
    ofxIO::DirectoryUtils::list("ISF", files, false, &pathFilter, true);

    for (std::size_t i = 0; i < files.size(); ++i){
        string name = files[i].substr(0, files[i].length()-3);
        ofxISF::Shader *isf;
        isf = new ofxISF::Shader();
        isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
        isf->load("ISF/" + name + ".fs");
        isfs.push_back(isf);
    }
}

void ISFLayer::update(){
    for (int i = 0; i < isfs.size(); i++) {
        if (currentISF == isfs[i]->getName()) {
            isfs[i]->update();
        }
    }
}

void ISFLayer::draw(){
    //ofSetColor(gain * 255);
    for (int i = 0; i < isfs.size(); i++) {
        if (currentISF == isfs[i]->getName()) {
            isfs[i]->draw(0, 0, ofGetWidth(), ofGetHeight());
        }
    }
}
