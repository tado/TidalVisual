//
//  ofxTidalISF.cpp
//  TidalISF
//
//  Created by Atsushi Tadokoro on 7/31/16.
//
//

#include "ofxTidalISF.hpp"

ofxTidalISF::ofxTidalISF(int _layer){
    layer = _layer;
    gain = 1.0;

    //init ISFs
    std::vector<std::string> files;
    ofxIO::DirectoryUtils::list("ISF", files, false, &pathFilter, true);
    ISFDirt *isf;
    for (std::size_t i = 0; i < files.size(); ++i){
        string name = files[i].substr(0, files[i].length()-3);
        cout << "files : " << name << endl;
        isf = new ISFDirt(name);
        isfDirts.push_back(isf);
    }
}

void ofxTidalISF::update(){
    for (int i = 0; i < isfDirts.size(); i++) {
        if (currentISF == isfDirts[i]->name) {
            isfDirts[i]->update();
        }
    }
}

void ofxTidalISF::draw(){
    ofSetColor(gain * 255);
    for (int i = 0; i < isfDirts.size(); i++) {
        if (currentISF == isfDirts[i]->name) {
            isfDirts[i]->draw();
        }
    }
}