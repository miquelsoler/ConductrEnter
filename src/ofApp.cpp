#include "ofApp.h"

const unsigned int LAST_SCENE = NUM_SCENES - 1;

#pragma mark - Main class methods

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);

    sceneManager.add(new Scene1("Scene1"));
    sceneManager.add(new Scene2("Scene2"));
    sceneManager.add(new Scene3("Scene3"));
    sceneManager.add(new Scene4("Scene4"));

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
    ofAddListener(scene4Timer.TIMER_COMPLETE, this,&ofApp::scene4TimerCompleteHandler);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (currentScene == LAST_SCENE) scene4Timer.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofxBitmapString(5.0f, ofGetHeight()-20.0f)
    << "SCENE INDEX: " << sceneManager.getCurrentSceneIndex() << endl
    << "SCENE NAME: " << sceneManager.getCurrentSceneName() << endl;

    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);
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
            sceneManager.prevScene();
            currentScene--;
            if (currentScene < 0) currentScene = NUM_SCENES-1;
            ofLog(OF_LOG_NOTICE, "Current scene: %d", currentScene);
            break;
        case OF_KEY_RIGHT:
            sceneManager.nextScene();
            currentScene = (currentScene + 1) % NUM_SCENES;
            ofLog(OF_LOG_NOTICE, "Current scene: %d", currentScene);
            break;
        case 'f':
            ofToggleFullscreen();
            break;
    }

    if (currentScene == LAST_SCENE)
    {
        // Setup timer for scene 4
        scene4Timer.setup(SCENE4_TIMER_MILLISECONDS);
        scene4Timer.start(true);
    }
    else
    {
        // Current scene isn't scene 4: reset timer
        scene4Timer.stop();
        scene4Timer.reset();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

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

