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
#include <ofxAppUtils.h>
#include "BaseScene.h"
#include "of3dPrimitives.h"
#include "ofxTweenzor.h"

typedef enum {
    Loop = 0,
    StartExplode = 1,
    Exploding = 2
} VideoState;

class Scene1 : public BaseScene
{
public:

    Scene1(const string& name, bool singleSetup) : BaseScene(name, singleSetup) {}

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();
    void exit();

private:

    // TUIO touch events
    virtual void tuioPressed(ofTouchEventArgs &touch);
    virtual void tuioReleased(ofTouchEventArgs &touch) {}
    virtual void tuioDragged(ofTouchEventArgs &touch) {}
    // Mouse events
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);

    int             loopFrame;
    VideoState      videoState; // 0 : loop     1 : start explode   2 : exploding
    float           videoHeaderFrame;
    void            goAhead();
    void            onVideoComplete(float* arg);
};

#endif /* defined(__ConductrEnter__Scene1__) */
