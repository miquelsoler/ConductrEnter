//
//  BaseScene.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 21/5/15.
//
//

#include "BaseScene.h"

#include "SettingsManager.h"

#pragma mark - Initialization

///--------------------------------------------------------------
BaseScene::BaseScene(const string& name, bool singleSetup) : ofxFadeScene(name)
{
    setSingleSetup(singleSetup);  // call setup each time the scene is loaded
    setFade(SettingsManager::getInstance().fade_in_milliseconds, SettingsManager::getInstance().fade_out_milliseconds);

    ofAddListener(ofEvents().windowResized, this, &BaseScene::windowResized);
}

#pragma mark - OF basic calls

///--------------------------------------------------------------
void BaseScene::setup()
{
}

///--------------------------------------------------------------
void BaseScene::updateEnter()
{
    ofxFadeScene::updateEnter();
}

///--------------------------------------------------------------
void BaseScene::update()
{
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

///--------------------------------------------------------------
void BaseScene::draw()
{
}

///--------------------------------------------------------------
void BaseScene::exit()
{
}

#pragma mark - Shared helper methods

///--------------------------------------------------------------
ofVec2f BaseScene::tuioToScreenCoords(float tuioX, float tuioY)
{
    ofVec2f screenCoords(ofMap(tuioX, 0, 1, 0, ofGetWidth()),
                         ofMap(tuioY, 0, 1, 0, ofGetHeight()));
    return screenCoords;
}
