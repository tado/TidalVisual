#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    
    //OSC
    receiver.setup(PORT);
    ofAddListener(receiver.messageReceived, this, &ofApp::oscReceiveEvent);
    receiver.start();
}

void ofApp::oscReceiveEvent(ofxOscMessage &m){
    if(m.getAddress() == "/play"){
        string name =  m.getArgAsString(0);
        currentISF = name;
        for (int j = 0; j < isfDirts.size(); j++) {
            isfDirts[j]->isf->setUniform<float>("vel", m.getArgAsFloat(1));
        }
        for (int j = 0; j < isfDirts.size(); j++) {
            isfDirts[j]->isf->setUniform<float>("gain", m.getArgAsFloat(2));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < isfDirts.size(); i++) {
        if (currentISF == isfDirts[i]->name) {
            isfDirts[i]->update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < isfDirts.size(); i++) {
        if (currentISF == isfDirts[i]->name) {
            isfDirts[i]->draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
