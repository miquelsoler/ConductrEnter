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

BaseScene::BaseScene(const string& name) : ofxFadeScene(name)
{
    setSingleSetup(false);  // call setup each time the scene is loaded
    setFade(SettingsManager::getInstance().fade_in_milliseconds, SettingsManager::getInstance().fade_out_milliseconds);
}

#pragma mark - OF basic calls

void BaseScene::setup()
{
}

void BaseScene::updateEnter()
{
    ofxFadeScene::updateEnter();
}

void BaseScene::update()
{
}

void BaseScene::updateExit()
{
    ofxFadeScene::updateExit();
}

void BaseScene::draw()
{
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 255 * alpha);	// alpha member variable for fade in/out

    drawScene();

    ofDisableAlphaBlending();
}

void BaseScene::exit()
{
}
