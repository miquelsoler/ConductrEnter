#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);

    scene1 = (Scene1 *)sceneManager.add(new Scene1("Scene1"));
    scene2 = (Scene2 *)sceneManager.add(new Scene2("Scene2"));
    scene3 = (Scene3 *)sceneManager.add(new Scene3("Scene3"));
    scene4 = (Scene4 *)sceneManager.add(new Scene4("Scene4"));
//    sceneManager.setup(true); // true = setup all the scenes now (not on the fly)
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

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    float x = (ofGetWidth() / 2.0f) - 80.0f;
    float y = ofGetHeight() / 2.0f;
    ofxBitmapString(x, y)
    << "SCENE INDEX: " << sceneManager.getCurrentSceneIndex() << endl
    << "SCENE NAME: " << sceneManager.getCurrentSceneName() << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
        case OF_KEY_LEFT:
            sceneManager.prevScene();
            break;
        case OF_KEY_RIGHT:
            sceneManager.nextScene();
            break;
        case 'f':
            ofToggleFullscreen();
            break;
    }
//    ofLog(OF_LOG_NOTICE, "Key pressed: %d", key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
