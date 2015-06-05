#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

#include "Config.h"

//========================================================================
int main( )
{
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    
    ofSetupOpenGL(&window, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_MODE);

    ofRunAppWithAppUtils(new ofApp());
}
