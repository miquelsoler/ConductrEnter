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

class BaseScene : public ofxFadeScene
{
public:

    BaseScene(const string& name, bool singleSetup);

    void setup();

    // called when scene is entering, this is just a demo and this
    // implementation is not required for this class
    void updateEnter();

    void update();

    // called when scene is exiting, this is just a demo and this
    // implementation is not required for this class
    void updateExit();

    void draw();

    // cleanup
    void exit();

    // Touch (currently mouse) events
    virtual void mouseMoved(int x, int y) = 0;
    virtual void mouseDragged(int x, int y, int button) = 0;
    virtual void mousePressed(int x, int y, int button) = 0;
    virtual void mouseReleased(int x, int y, int button) = 0;

    ofVideoPlayer videoPlayer;

protected:
    void drawPre();
    void drawPost();

    // Listener method to detect window changes
    virtual void windowResized(ofResizeEventArgs &args) {}
};

#endif /* defined(__ConductrEnter__BaseScene__) */
