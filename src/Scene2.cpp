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
}

///--------------------------------------------------------------
void Scene2::update()
{
}

///--------------------------------------------------------------
void Scene2::updateEnter()
{
    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene2::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene2::draw()
{
    BaseScene::drawPre();

    ofCircle(circleX, circleY, 50);
    ofxBitmapString(ofGetWidth()/2 - 80, ofGetHeight()/2) << "ARTISTS GO HERE" << endl;

    BaseScene::drawPost();
}

///--------------------------------------------------------------
void Scene2::exit()
{
}

#pragma mark - TUIO Touch events

///--------------------------------------------------------------
void Scene2::tuioPressed(ofVec2f &coords)
{
    ofVec2f screenCoords = tuioToScreenCoords(coords);
    circleX = screenCoords.x;
    circleY = screenCoords.y;
}

#pragma mark - Mouse events

///--------------------------------------------------------------
void Scene2::mouseDragged(int x, int y, int button)
{
}

///--------------------------------------------------------------
void Scene2::mousePressed(int x, int y, int button)
{
}

///--------------------------------------------------------------
void Scene2::mouseReleased(int x, int y, int button)
{
}
