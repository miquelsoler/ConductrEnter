//
//  Scene2.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__Scene2__
#define __ConductrEnter__Scene2__

#include <stdio.h>
#include "BaseScene.h"
#include "ofMain.h"

class Scene2 : public BaseScene
{
public:

    Scene2(const string& name, bool singleSetup) : BaseScene(name, singleSetup) {}

    void setup();
    void update();
    void updateEnter();
    void updateExit();
    void draw();
    void exit();

private:

    // TUIO touch events
    virtual void tuioPressed(ofTouchEventArgs &touch);
    virtual void tuioReleased(ofTouchEventArgs &touch) {};
    virtual void tuioDragged(ofTouchEventArgs &touch) {};

    virtual void tuioReceiverPressed(TUIOReceiverEvent &cursor);
    virtual void tuioReceiverReleased(TUIOReceiverEvent &cursor) {}
    virtual void tuioReceiverDragged(TUIOReceiverEvent &cursor) {}

    // Mouse events
    virtual void mousePressed(int x, int y, int button);

    ofVideoPlayer   videoPlayer;
};

#endif /* defined(__ConductrEnter__Scene2__) */
