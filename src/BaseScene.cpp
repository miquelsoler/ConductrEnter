//
//  BaseScene.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

#include "BaseScene.h"

BaseScene::BaseScene(const string& name) : ofxFadeScene(name)
{
    setSingleSetup(false);  // call setup each time the scene is loaded
    setFade(1000, 1000);    // 1 second fade in/out
}

void BaseScene::setup()
{

}

// called when scene is entering, this is just a demo and this
// implementation is not required for this class
void BaseScene::updateEnter()
{
    ofxFadeScene::updateEnter();
}

// normal update
void BaseScene::update()
{

}

// called when scene is exiting, this is just a demo and this
// implementation is not required for this class
void BaseScene::updateExit()
{
    ofxFadeScene::updateExit();
}

// draw
void BaseScene::draw()
{
}

// cleanup
void BaseScene::exit()
{
}

void BaseScene::enableAlphaBlendingForFade()
{
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 255*alpha);	// alpha member variable for fade in/out
}

void BaseScene::disableAlphaBlendingForFade()
{
    ofDisableAlphaBlending();
}
