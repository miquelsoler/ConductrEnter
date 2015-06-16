//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene2.h"
#include "TUIOHandler.h"

///--------------------------------------------------------------
void Scene2::setup()
{
    if (!videoPlayer.isLoaded()) videoPlayer.loadMovie("video/Artistas_0.mp4");
    videoPlayer.setLoopState(OF_LOOP_NONE);
}

///--------------------------------------------------------------
void Scene2::update()
{
    videoPlayer.update();
}

///--------------------------------------------------------------
void Scene2::updateEnter()
{
    videoPlayer.stop();
    videoPlayer.setFrame(0);
    videoPlayer.play();

    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene2::tuioReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene2::tuioDragged);
    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene2::updateExit()
{
    videoPlayer.stop();

    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene2::tuioReleased);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene2::tuioDragged);
    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene2::draw()
{
    BaseScene::drawPre();

    videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight() );

    BaseScene::drawPost();
}

///--------------------------------------------------------------
void Scene2::exit()
{
}

#pragma mark - TUIO Touch events

///--------------------------------------------------------------
void Scene2::tuioPressed(ofTouchEventArgs &touch)
{
    if (!videoPlayer.getIsMovieDone()) return;

    int sceneIndex = 1;
    ofNotifyEvent(eventGoToNextScene, sceneIndex, this);
}

#pragma mark - Mouse events

///--------------------------------------------------------------
void Scene2::mousePressed(int x, int y, int button)
{
    if (!videoPlayer.getIsMovieDone()) return;

    int sceneIndex = 1;
    ofNotifyEvent(eventGoToNextScene, sceneIndex, this);
}
