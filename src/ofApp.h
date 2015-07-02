#pragma once

#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ScreenSetup.h"
#include "ofxSimpleTimer.h"

const unsigned int NUM_SCENES = 2;
const unsigned int LAST_SCENE = NUM_SCENES - 1;

class ofApp : public ofxApp {

public:

    // Basic

    void setup();
    void update();
    void draw();

    // Interaction events
    void keyPressed(int key);
    void keyReleased(int key);

private:

    void goToNextScene();
    void goToPreviousScene();

    void goToScene2Artist(int &artistIndex);
    void goToScene1(bool &toLastVideoFrame);

    void drawScreenMode();
    void showScreenModeCompleteHandler(int &args);

    ofxSceneManager     sceneManager;
    unsigned int        currentScene;
//    ofxSimpleTimer      scene2Timer;

    ScreenSetup         screenSetup;
    bool                showScreenMode;
    ofxSimpleTimer      showScreenModeTimer;
    
    bool                showFPS;
};
