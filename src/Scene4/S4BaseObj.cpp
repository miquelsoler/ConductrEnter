//
//  S4BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S4BaseObj.h"
#include "ofxAppUtils.h"

const int LOOP_RESOLUTION = 50;

#pragma mark - Initialization

void S4BaseObj::initialize(float _viewOriginX, float _viewWidth, string _settingsPath)
{
    viewOriginX = _viewOriginX;
    viewWidth = _viewWidth;
    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, ofGetHeight());
    objPosition = ofPoint(viewOriginX + viewWidth/2.0f, ofGetHeight() / 2.0f);

    camera.disableMouseInput();

    settingsPath = _settingsPath;
    loadSettings();

#ifdef OF_DEBUG
    drawGui = true;
    gui.setPosition(viewOriginX, 50);
#endif
}

void S4BaseObj::drawLoop()
{
    // Draw loop arc
    loopArc.clear();
    loopArc.arc(objPosition, loopRadius, loopRadius, 0, 180, LOOP_RESOLUTION);
    loopArc.draw();
}
