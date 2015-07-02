//
//  Scene1.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

// TO DO
// * maybe might be usefull if we add "loopFrame" as a parameter on creation or setup
// * and so have this parameter "loopFrame" in the XML ?À to be able to change loop video without recompiling ?À
// * add the change to scene2 on completion.

#pragma once

#ifndef __ConductrEnter__Scene1__
#define __ConductrEnter__Scene1__

#include <stdio.h>
#include "ofxTweenzor.h"
#include <ofxAppUtils.h>
#include "ofxSimpleTimer.h"
#include "BaseScene.h"
#include "Scene1ArtistZone.h"


typedef enum {
    Loop = 0,
    StartExplode = 1,
    Exploding = 2
} VideoState;

typedef enum
{
    SceneStateIntro,
    SceneStateArtists
} SceneState;


class Scene1 : public BaseScene
{
public:

    Scene1(const string& name, bool singleSetup, ScreenSetup *screenSetup);

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void updateStateIntro();
    void updateStateArtists();
    void draw();
    void exit();

    void moveToLastVideoFrame();

private:

    // TUIO touch events
    virtual void tuioPressed(ofTouchEventArgs &touch);
    virtual void tuioReleased(ofTouchEventArgs &touch) {}
    virtual void tuioDragged(ofTouchEventArgs &touch) {}

    virtual void tuioReceiverPressed(TUIOReceiverEvent &cursor);
    virtual void tuioReceiverReleased(TUIOReceiverEvent &cursor) {}
    virtual void tuioReceiverDragged(TUIOReceiverEvent &cursor) {}

    // Mouse events
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseMoved(int x, int y);

    void handlePress(float x, float y);

    // Idle timer
    void leaveSceneTimerCompleteHandler(int &args);

    // Intro
    void skipIntro();
    void onVideoComplete(float* arg);

    // Artists
    int getTouchedArtistIndex(float percentX, float percentY);

    SceneState                  sceneState;

    ofVideoPlayer               videoPlayer;

    int                         loopFrame;
    VideoState                  videoState; // 0 : loop     1 : start explode   2 : exploding
    float                       videoHeaderFrame;

    vector<Scene1ArtistZone>    artistsZone;

    bool                        skipToLastVideoFrame;

    // Idle time handling
    ofxSimpleTimer          leaveSceneTimer;
    bool                    idleTimerStarted;
};

#endif /* defined(__ConductrEnter__Scene1__) */
