//
//  Scene2.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 21/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__Scene2__
#define __ConductrEnter__Scene2__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "ofxOsc.h"
#include "BaseScene.h"
#include "S2BaseObj.h"
#include "ofxTuioClient.h"
#include "TuioCursor.h"
#include "ofxSimpleTimer.h"


class Scene2 : public BaseScene
{
public:

    Scene2(const string& name, bool singleSetup, ScreenSetup *screenSetup);
    virtual ~Scene2();

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();
    void exit();

    void setArtistIndex(int artistIndex);
    void switchShowGUI();

private:

    // TUIO touch events
    virtual void tuioPressed(ofTouchEventArgs &touch);
    virtual void tuioReleased(ofTouchEventArgs &touch);
    virtual void tuioDragged(ofTouchEventArgs &touch);

    virtual void tuioReceiverPressed(TUIOReceiverEvent &cursor);
    virtual void tuioReceiverReleased(TUIOReceiverEvent &cursor);
    virtual void tuioReceiverDragged(TUIOReceiverEvent &cursor);

    // Mouse events
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);

    // Interaction handling
    typedef enum
    {
        InteractionSourceTuio,
        InteractionSourceMouse
    } InteractionSource;

    void handlePress(InteractionSource interactionSource, int x, int y, TuioCursor *cursor = NULL);
    void handleRelease(InteractionSource interactionSource, int x, int y, int cursorId = -1); // CursorId is the id received during the release event
    void handleDrag(InteractionSource interactionSource, int x, int y, int cursorId = -1); // CursorId is the id received during the drag event

    // Listeners
    virtual void windowResized(ofResizeEventArgs &args);
    virtual void tempoChanged(float &newTempo);

    // Idle timer
    void leaveSceneTimerCompleteHandler(int &args);

    // Helper methods
    unsigned int getObjectIndexAtX(int x);
    int getObjectIndexWithCursor(int cursorId);
    unsigned int getClipIndexAtY(int y);
    TuioCursor *makeCursor(int cursorId, float x, float y);
    TuioCursor *makeCursor(int sourceId, int sessionId, int cursorId, float x, float y, float xSpeed, float ySpeed, float motionAccel);

    int                     artistIndex = 0;
    unsigned int            mouseObjectIndex;

    unsigned int            currentClipIndex;
    unsigned int            artistOffset;

    vector<S2BaseObj *>     objects;
    unsigned int            numObjects;
    float                   viewWidth, viewHeight;
    float                   clipHeight;

    ofVideoPlayer           videoPlayer;

    ofImage                 bgImage1;
    ofImage                 bgImage2;
    float                   bgImageScale;
    float                   bgImageAlpha;

    // Idle time handling
    ofxSimpleTimer          leaveSceneTimer;
//    unsigned int            numberOfTouches;
//    bool                    idleTimerStarted;
};

#endif /* defined(__ConductrEnter__Scene2__) */
