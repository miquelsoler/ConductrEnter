#pragma once

#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxSimpleTimer.h"

#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"

class ofApp : public ofxApp {

public:

    // Basic

    void setup();
    void update();
    void draw();

    // Interaction events

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    // Scenes

    ofxSceneManager sceneManager;
    int currentScene = 0;

    ofxSimpleTimer scene4Timer;
    void scene4TimerCompleteHandler(int &args);
};
