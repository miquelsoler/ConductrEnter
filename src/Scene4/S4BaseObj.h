//
//  S4BaseObj.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4BaseObj__
#define __ConductrEnter__S4BaseObj__

#include <stdio.h>

#include "ofEasyCam.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofTrueTypeFont.h"

class S4BaseObj
{
public:

    virtual ~S4BaseObj() {}

    void initialize(float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

protected:

    void drawLoop();
    virtual void loadSettings() = 0;
    
    // Camera & viewport
    ofEasyCam camera;
    ofRectangle viewRectangle;
    float viewOriginX, viewWidth;

    // Object parameters
    ofPoint objPosition;
    ofParameter<int> camDistance;

    // Loop arc
    ofPolyline loopArc;
    ofParameter<int> loopRadius;
    ofParameter<int> loopAngle;
    float loopTimePerCycle;
    unsigned int loopFrequency;

    // GUI
    ofxPanel gui;
    string settingsPath;
    ofTrueTypeFont guiFont;
    bool drawGui = false;


/*
    ofParameter<float> loopRadius;
*/
};

#endif /* defined(__ConductrEnter__S4BaseObj__) */
