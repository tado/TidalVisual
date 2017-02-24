#include "StISFView.hpp"

void StISFView::setup(){
    name = "StISFView";
    app = ((ofApp*)ofGetAppPtr());
    
    //init ISFs
    std::vector<std::string> files;
    ofxIO::DirectoryUtils::list("ISF", files, false, &pathFilter, true);
    isfNum = 0;
    lastNum = 0;
    
    for (std::size_t i = 0; i < files.size(); ++i){
        string name = files[i].substr(0, files[i].length()-3);
        ofxISF::Shader *isf;
        isf = new ofxISF::Shader();
        isf->setup(ofGetWidth()/2, ofGetHeight()/2, GL_RGB32F);
        isf->load("ISF/" + name + ".fs");
        isfs.push_back(isf);
    }
}

void StISFView::update(){
    /*
    for (int i = 0; i < app->tidal->notes.size(); i++) {
        //isfNum = app->tidal->notes[i].instNum % isfs.size();
        isfNum = ofRandom(isfs.size());
    }
    */
    
    if (app->tidal->instNumMax > 0 && app->tidal->notes.size() > 0){
        if (lastNum != app->tidal->noteCount) {
            isfNum = ofRandom(app->tidal->instNumMax % isfs.size());
            /*
            while(1){
                isfNum = ofRandom(app->tidal->instNumMax % isfs.size());
                if (isfNum != lastNum) {
                    break;
                }
            }
            */
        }
        lastNum = app->tidal->noteCount;
    }
    isfs[isfNum]->update();

    /*
     if (app->tidal->instNumMax > 0 && app->tidal->notes.size() > 0) {
     isfNum = app->tidal->notes[app->tidal->notes.size()-1].instNum;
     }
     
    if (app->tidal->instNumMax > 0 && app->tidal->notes.size() > 0){
        if (lastNum != app->tidal->noteCount) {
            while(1){
                isfNum = ofRandom(isfs.size()-1);
                if (isfNum != lastNum) {
                    break;
                }
            }
        }
        lastNum = app->tidal->noteCount;
    }
    */
    
}

void StISFView::draw(){
    //for (int i = 0; i < isfs.size(); i++) {
    //if (currentISF == isfs[i]->getName()) {
    isfs[isfNum]->draw(0, 0, ofGetWidth(), ofGetHeight());
    //}
    //}
}


void StISFView::stateExit(){
    
}

void StISFView::stateEnter(){
    
}

string StISFView::getName(){
    return name;
}
