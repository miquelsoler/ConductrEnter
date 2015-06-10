//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene2.h"

void Scene2::setup()
{
}

void Scene2::update()
{
}

void Scene2::draw()
{
    BaseScene::drawPre();

    ofxBitmapString(ofGetWidth()/2 - 80, ofGetHeight()/2) << "ARTISTS GO HERE" << endl;

    BaseScene::drawPost();
}

void Scene2::exit()
{
}

#pragma mark - Touch events

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
