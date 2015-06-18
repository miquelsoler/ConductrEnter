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

    bool pick(int screenX, int screenY);
    void unpick();
    bool getIsPicked();
    void enablePinch(bool enable);
    bool isPinchEnabled();
    virtual void updatePinch();
    int getFirstCursorId();

    void addCursor(int cursorId);
    void removeLastCursor();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);
    void setAnimated(bool animate);

    virtual void volumeChanged(float &newVolume) = 0;

protected:

    void drawLoop();
    void drawWhiteCircle();
    virtual void loadSettings() = 0;
    void initSharedSettings();
    virtual void windowResized(ofResizeEventArgs &args);

    // Camera & viewport
    ofEasyCam           camera;
    ofParameter<int>    camDistance;

    // Object parameters
    float               radius;
    bool                isAnimated = 0;
    bool                isPicked = false;

    // Circles
    ofParameter<float>  whiteCircleRadius;
    float               pinchCircleRadius;

    // TUIO
    list<int>           cursorIds;
    bool                pinchEnabled = false;
    float               pinchInitialDist;

    // Loop arc
    ofPolyline          loopArc;
    ofParameter<int>    loopRadius;
    ofParameter<int>    loopAngle;
    float               loopTimePerCycle;
    unsigned int        loopFrequency;

    // GUI
    ofxPanel            gui;
    string              settingsPath;
};

#endif /* defined(__ConductrEnter__S4BaseObj__) */
