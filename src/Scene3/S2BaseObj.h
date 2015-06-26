//
//  S2BaseObj.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2BaseObj__
#define __ConductrEnter__S2BaseObj__

#include <stdio.h>

#include "BaseObject.h"
#include "ofEasyCam.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofTrueTypeFont.h"
#include "ofxTuioClient.h"
#include "TuioCursor.h"

typedef enum
{
    S3ObjStateInactive = 0,
    S3ObjStateTransitioning = 1,
    S3ObjStateActive = 2
} S3ObjState;


class S2BaseObj : public BaseObject
{
public:
    S2BaseObj(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);
    virtual ~S2BaseObj() {}

    virtual void setup();
    virtual void update();
    virtual void draw(int x,int y,int w,int h);
    virtual void drawIntoFbo();
    
    bool pick(int screenX, int screenY);
    void unpick();
    bool getIsPicked();
    void enablePinch(bool enable);
    bool isPinchEnabled();
    virtual void updatePinch();

    TuioCursor *getFirstCursor();
    TuioCursor *getLastCursor();

    void addCursor(TuioCursor *cursor);
    void removeLastCursor();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

    void play();
    void stop();

    virtual void volumeChanged(float &newVolume) = 0;
    virtual void clipPositionChanged(float &newPosition);
    
    // FBO
    ofFbo           fbo;
    bool            showGUI;


protected:

    // Managing states

    void changeState();

    virtual void initInactive() = 0;
    virtual void updateInactive() = 0;
    virtual void drawInactive() = 0;

    virtual void initTransitioning() = 0;
    virtual void updateTransitioning() = 0;
    virtual void drawTransitioning() = 0;

    virtual void initActive() = 0;
    virtual void updateActive() = 0;
    virtual void drawActive() = 0;

    // Extra draws

    void drawLoop();
    void drawWhiteCircle();
    void drawPinchCircle();

    virtual void loadSettings() = 0;
    void initSharedSettings();
    virtual void windowResized(ofResizeEventArgs &args);

    bool                    isFirstSetup;

    ofParameter<bool>       activate;
    
    // Camera & viewport
    ofEasyCam               camera;
    ofParameter<int>        camDistance;

    // Object state
    S3ObjState              currentState;
    S3ObjState              nextState;
    bool                    shouldChangeState;
    ofEvent<void>           eventChangeState;

    // Object parameters
    float                   radius;
    bool                    isPicked = false;

    // Circles
    ofParameter<float>      whiteCircleRadius;
    ofImage                 pinchImage;
    float                   pinchImageSize;
    unsigned int            pinchImageAlpha;
    unsigned int            pinchImageAlphaMin, pinchImageAlphaMax;

    // TUIO
    list<TuioCursor *>      cursorIds;
    bool                    pinchEnabled = false;
    float                   pinchInitialDist;

    // Loop arc
    ofPolyline              loopArc;
    ofParameter<int>        loopRadius;
    ofParameter<int>        loopInitialAngle;
    float                   loopAngle = 0;

    // GUI
    ofxPanel                gui;
    string                  settingsPath;
};

#endif /* defined(__ConductrEnter__S2BaseObj__) */
