#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //ofSetupOpenGL(1680/2, 1050, OF_WINDOW);			// <-------- setup the GL context
    //ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context
    ofSetupOpenGL(1920/2,1080,OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
