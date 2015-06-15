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
    circleX = ofGetWidth()/2;
    circleY = ofGetHeight()/2;
    circleRadius = 20;
}

///--------------------------------------------------------------
void Scene2::update()
{
}

///--------------------------------------------------------------
void Scene2::updateEnter()
{
    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene2::tuioReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene2::tuioDragged);
    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene2::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene2::tuioReleased);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene2::tuioDragged);
    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene2::draw()
{
    BaseScene::drawPre();

    ofCircle(circleX, circleY, circleRadius);
    ofxBitmapString(ofGetWidth()/2 - 80, ofGetHeight()/2) << "ARTISTS GO HERE" << endl;

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
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    circleX = screenCoords.x;
    circleY = screenCoords.y;
    circleRadius = 50;
}

///--------------------------------------------------------------
void Scene2::tuioReleased(ofTouchEventArgs &touch)
{
    circleRadius = 20;
}

///--------------------------------------------------------------
void Scene2::tuioDragged(ofTouchEventArgs &touch)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    circleX = screenCoords.x;
    circleY = screenCoords.y;
    circleRadius = 50;
}


#pragma mark - Mouse events

///--------------------------------------------------------------
void Scene2::mouseDragged(int x, int y, int button)
{
    circleX = x;
    circleY = y;
}

///--------------------------------------------------------------
void Scene2::mousePressed(int x, int y, int button)
{
    circleX = x;
    circleY = y;
}

///--------------------------------------------------------------
void Scene2::mouseReleased(int x, int y, int button)
{
}
