//
//  BaseScene.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "BaseScene.h"

#pragma mark - Initialization

///--------------------------------------------------------------
BaseScene::BaseScene(const string& name, bool singleSetup, ScreenSetup *_screenSetup) : ofxFadeScene(name)
{
    screenSetup = _screenSetup;

    setSingleSetup(singleSetup);  // call setup each time the scene is loaded
    setFade(0, 0);

    ofAddListener(ofEvents().windowResized, this, &BaseScene::windowResized);
}

#pragma mark - OF basic calls

///--------------------------------------------------------------
void BaseScene::updateEnter()
{
    AbletonManager::getInstance().stopAll();

    ofxFadeScene::updateEnter();
}

///--------------------------------------------------------------
void BaseScene::updateExit()
{
    AbletonManager::getInstance().stopAll();

    ofxFadeScene::updateExit();
}

///--------------------------------------------------------------
void BaseScene::drawPre()
{
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, (int)(255 * alpha));	// alpha member variable for fade in/out
}

///--------------------------------------------------------------
void BaseScene::drawPost()
{
    ofDisableAlphaBlending();
}
