//
//  BaseScene.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "BaseScene.h"

#include "SettingsManager.h"

#pragma mark - Initialization

///--------------------------------------------------------------
BaseScene::BaseScene(const string& name, bool singleSetup) : ofxFadeScene(name)
{
    setSingleSetup(singleSetup);  // call setup each time the scene is loaded
    setFade(SettingsManager::getInstance().sceneFadeInMilliseconds, SettingsManager::getInstance().sceneFadeOutMilliseconds);

    ofAddListener(ofEvents().windowResized, this, &BaseScene::windowResized);
}

#pragma mark - OF basic calls

///--------------------------------------------------------------
void BaseScene::updateEnter()
{
    ofxFadeScene::updateEnter();
}

///--------------------------------------------------------------
void BaseScene::updateExit()
{
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
