#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(1600,450,OF_WINDOW);			// <-------- setup the GL context

//	ofRunApp(new ofApp());
    ofRunAppWithAppUtils(new ofApp());
}
