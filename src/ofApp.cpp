#include "ofApp.h"

#include "TUIOHandler.h"
#include "Defaults.h"
#include "SettingsManager.h"

#include "BaseScene.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"

#pragma mark - Main class methods

///--------------------------------------------------------------
void ofApp::setup()
{
    // App settings

    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    ofBackground(ofColor::black);

    // TUIO
    TUIOHandler::getInstance().init();

    // Tweenzor (must call this before adding any tweens)
    Tweenzor::init();

    // Scenes
    Scene1 *scene1 = new Scene1("Scene1", true);
    ofAddListener(scene1->eventGoToNextScene, this, &ofApp::goToNextScene);
    sceneManager.add(scene1);

    Scene2 *scene2 = new Scene2("Scene2", true);
    ofAddListener(scene2->eventGoToNextScene, this, &ofApp::goToNextScene);
    sceneManager.add(scene2);

    sceneManager.add(new Scene3("Scene3", true));

    sceneManager.setup(true); // call setup for all of them
    sceneManager.setOverlap(false); // overlap scenes when transitioning

    // attach scene manager to this ofxApp so it's called automatically,
    // you can also call the callbacks (update, draw, keyPressed, etc) manually
    // if you don't set it
    //
    // you can also turn off the auto sceneManager update and draw calls with:
    // setSceneManagerUpdate(false);
    // setSceneManagerDraw(false);
    //
    // the input callbacks in your scenes will be called if they are implemented
    //
    setSceneManager(&sceneManager);

    // Timer listener for scene 3
    manageScene3Timer();
    ofAddListener(scene3Timer.TIMER_COMPLETE, this, &ofApp::scene3TimerCompleteHandler);

    sceneManager.gotoScene(SettingsManager::getInstance().sceneFirstScene);
}

///--------------------------------------------------------------
void ofApp::update()
{
    if (currentScene == LAST_SCENE) scene3Timer.update();

    if (sceneManager.getCurrentSceneIndex() == -1) sceneManager.gotoScene(currentScene);

#ifdef OF_DEBUG
    ofShowCursor();
#endif
}

///--------------------------------------------------------------
void ofApp::draw()
{
#ifdef OF_DEBUG
    ofSetColor(ofColor::gray);
    ofxBitmapString(5.0f, ofGetHeight()-20.0f)
    << "SCENE INDEX: " << sceneManager.getCurrentSceneIndex() << endl
    << "SCENE NAME: " << sceneManager.getCurrentSceneName() << endl;

    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", ofGetWidth() - 100, ofGetHeight() - 15);
#endif
}

#pragma mark - Interaction events

///--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key)
    {
        case OF_KEY_LEFT: {
            goToPreviousScene();
            break;
        }
        case OF_KEY_RIGHT: {
            goToNextScene();
            break;
        }
        case 'f':
        case 'F': {
            int windowMode = ofGetWindowMode();
            bool fullscreen = (windowMode == OF_WINDOW);
            ofSetWindowShape(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
            ofSetFullscreen(fullscreen);
            break;
        }
        default:
            break;
    }
}

#pragma mark - Scene management

///--------------------------------------------------------------
void ofApp::goToNextScene()
{
    sceneManager.nextScene();
    currentScene = (currentScene + 1) % NUM_SCENES;
}

///--------------------------------------------------------------
void ofApp::goToNextScene(int &senderSceneIndex)
{
    goToNextScene();
}

///--------------------------------------------------------------
void ofApp::goToPreviousScene()
{
    sceneManager.prevScene();
    if (currentScene == 0)
        currentScene = LAST_SCENE;
    else
        currentScene--;

    manageScene3Timer();
}

///--------------------------------------------------------------
void ofApp::manageScene3Timer()
{
//    if (currentScene == LAST_SCENE)
//    {
//        // Scene is #4, init timer for it
//        scene3Timer.setup(SettingsManager::getInstance().scene3TimerMilliseconds);
//        scene3Timer.start(true);
//    }
//    else
//    {
//        // Scene isn't #4, reset its timer
//        scene3Timer.stop();
//        scene3Timer.reset();
//    }
}

///--------------------------------------------------------------
void ofApp::scene3TimerCompleteHandler(int &args)
{
    ofLog(OF_LOG_NOTICE, "Timer completed. Jump to scene 1.");
    scene3Timer.stop();
    currentScene = 0;
    sceneManager.gotoScene(currentScene);
}
