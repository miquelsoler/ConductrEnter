//
//  BaseScene.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#ifndef __ConductrEnter__BaseScene__
#define __ConductrEnter__BaseScene__

#pragma once

#include <stdio.h>
#include <ofxAppUtils.h>
#include "ofVideoPlayer.h"
#include "ofMain.h"
#include "TUIOReceiverEvent.h"
#include "ScreenSetup.h"

typedef enum
{
    SceneBgModeNone = 0,
    SceneBgModeVideo = 1,
    SceneBgModeImages = 2
} SceneBgMode;

class BaseScene : public ofxFadeScene
{
public:

    BaseScene(const string& name, bool singleSetup, ScreenSetup *screenSetup);

    void setup() {};

    // called when scene is entering, this is just a demo and this
    // implementation is not required for this class
    void updateEnter();

    // called when scene is exiting, this is just a demo and this
    // implementation is not required for this class
    void updateExit();

    // cleanup
    void exit() {};

    ofEvent<int> eventGoToArtist;

protected:

    void drawPre();
    void drawPost();

    // Local TUIO touch events
    virtual void tuioPressed(ofTouchEventArgs &touch) = 0;
    virtual void tuioReleased(ofTouchEventArgs &touch) = 0;
    virtual void tuioDragged(ofTouchEventArgs &touch) = 0;

    // Remote TUIO touch events
    virtual void tuioReceiverPressed(TUIOReceiverEvent &cursor) = 0;
    virtual void tuioReceiverReleased(TUIOReceiverEvent &cursor) = 0;
    virtual void tuioReceiverDragged(TUIOReceiverEvent &cursor) = 0;

    // Touch (currently mouse) events
    virtual void mouseDragged(int x, int y, int button) {};
    virtual void mousePressed(int x, int y, int button) {};
    virtual void mouseReleased(int x, int y, int button) {};

    // Listener method to detect window changes
    virtual void windowResized(ofResizeEventArgs &args) {}

    ScreenSetup *screenSetup;

    SceneBgMode backgroundMode;
};

#endif /* defined(__ConductrEnter__BaseScene__) */
