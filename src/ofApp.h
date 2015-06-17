#pragma once

#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxSimpleTimer.h"

const unsigned int NUM_SCENES = 3;
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
    void goToNextScene(int &senderSceneIndex);
    void goToPreviousScene();
    void manageScene3Timer();
    void scene3TimerCompleteHandler(int &args);

    ofxSceneManager     sceneManager;
    unsigned int        currentScene;
    ofxSimpleTimer      scene3Timer;
};
