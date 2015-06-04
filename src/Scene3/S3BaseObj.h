//
//  S3BaseObj.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3BaseObj__
#define __ConductrEnter__S3BaseObj__

#include <stdio.h>

#include "ofEasyCam.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofTrueTypeFont.h"

class S3BaseObj
{
public:

    S3BaseObj() {}

    void initialize(float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void setY(float newY) = 0; // Nœria
    float getViewOriginX();
    void setAnimated(bool animate);

protected:

    void drawLoop();
    virtual void loadSettings() = 0;
    
    // Camera & viewport
    ofEasyCam camera;
    ofRectangle viewRectangle;
    float viewOriginX, viewWidth, viewHalfWidth, viewHalfHeight;
    ofParameter<int> camDistance;

    // Object parameters
    ofPoint objPosition;
    bool isAnimated = 0;

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
};

#endif /* defined(__ConductrEnter__S4BaseObj__) */
