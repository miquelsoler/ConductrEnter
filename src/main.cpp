#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"


//========================================================================
int main( ){
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window, WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);
//    ofSetupOpenGL(1600,450,OF_WINDOW);			// <-------- setup the GL context

    ofRunAppWithAppUtils(new ofApp());
}
