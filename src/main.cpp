#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

static const unsigned int   DEFAULT_WINDOW_WIDTH        = 1280;
static const unsigned int   DEFAULT_WINDOW_HEIGHT       = 720;

//========================================================================
int main( )
{
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    
    ofSetupOpenGL(&window, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, OF_WINDOW);

    ofRunAppWithAppUtils(new ofApp());
}
