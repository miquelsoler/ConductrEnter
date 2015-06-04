#include "ofApp.h"

#include "SettingsManager.h"

#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"


#pragma mark - Main class methods

//--------------------------------------------------------------
void ofApp::setup()
{
    // App settings

    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    ofBackground(0, 0, 0);

    // Scenes

    sceneManager.add(new Scene1("Scene1"));
    sceneManager.add(new Scene2("Scene2"));
    sceneManager.add(new Scene3("Scene3"));
//    sceneManager.add(new Scene4("Scene4"));


    sceneManager.gotoScene(currentScene);

    // overlap scenes when transitioning
    sceneManager.setOverlap(true);

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

    // Timer listener for scene 4
    manageScene4Timer();
    ofAddListener(scene4Timer.TIMER_COMPLETE, this,&ofApp::scene4TimerCompleteHandler);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (currentScene == LAST_SCENE) scene4Timer.update();

#ifdef OF_DEBUG
    ofShowCursor();
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
#ifdef OF_DEBUG
    ofxBitmapString(5.0f, ofGetHeight()-20.0f)
    << "SCENE INDEX: " << sceneManager.getCurrentSceneIndex() << endl
    << "SCENE NAME: " << sceneManager.getCurrentSceneName() << endl;

    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
#endif
}

#pragma mark - Interaction events

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key)
    {
        case OF_KEY_LEFT:
            goToPreviousScene();
            break;
        case OF_KEY_RIGHT:
            goToNextScene();
            break;
        case 'f':
            ofToggleFullscreen();
        cout << ofGetWidth() << "x" << ofGetHeight() << endl;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    switch (button) {
//        case OF_MOUSE_BUTTON_LEFT:
//            goToNextScene();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    int numScenes = sceneManager.getNumScenes();
    for (int i=0; i<numScenes; i++)
    {
        BaseScene *scene = (BaseScene *)(sceneManager.getSceneAt(i));
        scene->setup();
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#pragma mark - Timers

void ofApp::scene4TimerCompleteHandler(int &args)
{
    ofLog(OF_LOG_NOTICE, "Timer completed. Jump to scene 1.");
    scene4Timer.stop();
    currentScene = 0;
    sceneManager.gotoScene(currentScene);
}

#pragma mark - Scene management

void ofApp::goToNextScene()
{
    sceneManager.nextScene();
    currentScene = (currentScene + 1) % NUM_SCENES;
}

void ofApp::goToPreviousScene()
{
    sceneManager.prevScene();
    currentScene--;
    if (currentScene < 0) currentScene = NUM_SCENES-1;

    manageScene4Timer();
}

void ofApp::manageScene4Timer()
{
    if (currentScene == LAST_SCENE)
    {
        // Scene is #4, init timer for it
        scene4Timer.setup(SettingsManager::getInstance().scene4_timer_milliseconds);
        scene4Timer.start(true);
    }
    else
    {
        // Scene isn't #4, reset its timer
        scene4Timer.stop();
        scene4Timer.reset();
    }
}
