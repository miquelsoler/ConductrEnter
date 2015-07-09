#include "ofApp.h"

#include "TUIOHandler.h"
#include "AbletonManager.h"
#include "SettingsManager.h"

#include "BaseScene.h"
#include "Scene1.h"
#include "Scene2.h"

#pragma mark - Main class methods

///--------------------------------------------------------------
void ofApp::setup()
{
#ifdef OF_DEBUG
    showFPS = SettingsManager::getInstance().debugShowFPS;
#else
    showFPS = SettingsManager::getInstance().releaseShowFPS;
#endif

    showScreenMode = false;
    screenSetup.setScreenMode(SCREENMODE_DISPLAX);
    
    // App settings

    ofSetFrameRate(60);
    bool enableVerticalSync;
#ifdef OF_DEBUG
    enableVerticalSync = SettingsManager::getInstance().debugEnableVSync;
#else
    enableVerticalSync = SettingsManager::getInstance().releaseEnableVSync;
#endif
    ofSetVerticalSync(enableVerticalSync);

    ofBackground(ofColor::black);

    // TUIO
    TUIOHandler::getInstance().init();

    // Ableton
    string host = SettingsManager::getInstance().abletonHost;
    unsigned int senderPort = SettingsManager::getInstance().abletonSenderPort;
    unsigned int receiverPort = SettingsManager::getInstance().abletonReceiverPort;
    AbletonManager::getInstance().init(host, senderPort, receiverPort);

    // Tweenzor (must call this before adding any tweens)
    Tweenzor::init();

    // Scenes
    Scene1 *scene1 = new Scene1("Scene1", true, &screenSetup);
    ofAddListener(scene1->eventGoToPlayground, this, &ofApp::goToScene2Artist);
    sceneManager.add(scene1);


    Scene2 *scene2 = new Scene2("Scene2", true, &screenSetup);
    ofAddListener(scene2->eventGoToArtists, this, &ofApp::goToScene1);
    sceneManager.add(scene2);

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

    sceneManager.gotoScene(SettingsManager::getInstance().sceneFirstScene);
}

///--------------------------------------------------------------
void ofApp::update()
{
//    ofBackground(ofColor(255,0,0,255));
    
    if (sceneManager.getCurrentSceneIndex() == -1) sceneManager.gotoScene(currentScene);

#ifdef OF_DEBUG
    ofShowCursor();
#endif
    showScreenModeTimer.update();

    TUIOHandler::getInstance().update();
}

///--------------------------------------------------------------
void ofApp::draw()
{
    // Draw screen mode
    if (showScreenMode) drawScreenMode();

    if (showFPS)
    {
        ofSetColor(ofColor::gray);
        ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 20, ofGetHeight() - 15);
    }
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
        case OF_KEY_LEFT:
        {
            // Go to previous scene
            goToPreviousScene();
            break;
        }
        case OF_KEY_RIGHT:
        {
            // Go to next scene
            goToNextScene();
            break;
        }
        case 'f':
        case 'F':
        {
            // Change window mode
            screenSetup.changeToNextMode();

            showScreenModeTimer.stop();
            showScreenMode = true;
            showScreenModeTimer.setup(3000);
            ofAddListener(showScreenModeTimer.TIMER_COMPLETE, this, &ofApp::showScreenModeCompleteHandler);
            showScreenModeTimer.start(false);

            break;
        }
        case 'g':
        case 'G':
        {
            // Show GUI
            Scene2 *scene2 = (Scene2 *)sceneManager.getSceneAt(1);
            scene2->switchShowGUI();
            break;
        }
        case 'p':
        case 'P':
        {
            // Show FPS
            showFPS=!showFPS;
            break;
        }
        case 'R':
        {
            // Restart app
            appRestarter.restart(SettingsManager::getInstance().restartDelay, SettingsManager::getInstance().restartShowMessage);
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
void ofApp::goToPreviousScene()
{
    sceneManager.prevScene();
    if (currentScene == 0)
        currentScene = LAST_SCENE;
    else
        currentScene--;
}

///--------------------------------------------------------------
void ofApp::goToScene1(bool &toLastVideoFrame)
{
    Scene1 *scene1 = (Scene1 *)sceneManager.getSceneAt(0);
    if (toLastVideoFrame)
        scene1->moveToLastVideoFrame();
    goToNextScene();
}

///--------------------------------------------------------------
void ofApp::goToScene2Artist(int &artistIndex)
{
    Scene2 *scene2 = (Scene2 *)sceneManager.getSceneAt(1);
    scene2->setArtistIndex(artistIndex);
    goToNextScene();
}

///--------------------------------------------------------------
void ofApp::drawScreenMode()
{
    float halfWindowWidth = ofGetWidth() / 2;
    float halfWindowHeight = ofGetHeight() / 2;
    float textXOffset = 98;
    float textYOffset = 8;
    float textX = halfWindowWidth - textXOffset;
    float textY = halfWindowHeight - textYOffset;
    float rectOffset = 12;

    ofFill();
    ofSetColor(50, 125, 50, 200);
    ofRect(textX-rectOffset, textY-2*rectOffset, 2*textXOffset + 2*rectOffset, 2*textYOffset + 2*rectOffset);
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Screen Mode: " + screenSetup.getCurrentScreenModeString(), textX, textY);
    ofDrawBitmapString("Screen Mode: " + screenSetup.getCurrentScreenModeString(), textX+1, textY);
}

///--------------------------------------------------------------
void ofApp::showScreenModeCompleteHandler(int &args)
{
    showScreenMode = false;
    showScreenModeTimer.stop();
    ofRemoveListener(showScreenModeTimer.TIMER_COMPLETE, this, &ofApp::showScreenModeCompleteHandler);
}
