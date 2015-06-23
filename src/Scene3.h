//
//  Scene3.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__Scene3__
#define __ConductrEnter__Scene3__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "ofxOsc.h"
#include "BaseScene.h"
#include "S3BaseObj.h"
#include "AbletonManager.h"
#include "ofxTuioClient.h"
#include "TuioCursor.h"

const unsigned int NUM_CLIPS = 5;
const unsigned int DEFAULT_CLIP = 2;

class Scene3 : public BaseScene
{
public:

    Scene3(const string& name, bool singleSetup);
    virtual ~Scene3();

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();
    void exit();

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
    void handlePress(int x, int y, TuioCursor *cursor = NULL);
    void handleRelease(int x, int y, int cursorId = -1); // CursorId is the id received during the release event
    void handleDrag(int x, int y, int cursorId = -1); // CursorId is the id received during the drag event

    // Listeners
    virtual void windowResized(ofResizeEventArgs &args);
    virtual void tempoChanged(float &newTempo);

    // Helper methods
    unsigned int getObjectIndexAtX(int x);
    unsigned int getClipIndexAtY(int y);
    TuioCursor *makeCursor(int cursorId, float x, float y);
    TuioCursor *makeCursor(int sourceId, int sessionId, int cursorId, float x, float y, float xSpeed, float ySpeed, float motionAccel);

    AbletonManager*         abletonManager;
    unsigned int            currentClipIndex;

    vector<S3BaseObj*>      objects;
    unsigned int            num_objects;
    float                   viewWidth, viewHeight;
    float                   clipHeight;
};

#endif /* defined(__ConductrEnter__Scene4__) */
