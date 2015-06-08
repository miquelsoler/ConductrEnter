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

#include "BaseObject.h"
#include "ofEasyCam.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofTrueTypeFont.h"

class S3BaseObj : public BaseObject
{
public:
    S3BaseObj(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);
    virtual ~S3BaseObj() {}

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void setY(float newY) = 0;
    void setAnimated(bool animate);

protected:

    void drawLoop();
    virtual void loadSettings() = 0;
    void initSharedSettings();

    // Camera & viewport
    ofEasyCam camera;
    ofParameter<int> camDistance;

    // Object parameters
    float radius;
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

    // Resizes
    virtual void windowResized(ofResizeEventArgs &args);
};

#endif /* defined(__ConductrEnter__S4BaseObj__) */
