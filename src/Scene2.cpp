//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene2.h"
#include "TUIOHandler.h"

void Scene2::setup()
{
    circleX = ofGetWidth()/2;
    circleY = ofGetHeight()/2;
}

void Scene2::update()
{
}

void Scene2::updateEnter()
{
    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioTouchedDown);
    BaseScene::updateEnter();
}

void Scene2::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioTouchedDown);
    BaseScene::updateExit();
}

void Scene2::draw()
{
    BaseScene::drawPre();

    ofCircle(circleX, circleY, 50);
    ofxBitmapString(ofGetWidth()/2 - 80, ofGetHeight()/2) << "ARTISTS GO HERE" << endl;

    BaseScene::drawPost();
}

void Scene2::exit()
{
}

#pragma mark - Touch events

void Scene2::tuioTouchedDown(ofVec2f &coords)
{
    circleX = ofMap(coords.x, 0, 1, 0, ofGetWidth());
    circleY = ofMap(coords.y, 0, 1, 0, ofGetHeight());
    cout << coords.x << "," << coords.y << endl;
}

void Scene2::mouseMoved(int x, int y)
{
}

void Scene2::mouseDragged(int x, int y, int button)
{
}

void Scene2::mousePressed(int x, int y, int button)
{
}

void Scene2::mouseReleased(int x, int y, int button)
{
}
