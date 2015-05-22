//
//  BaseScene.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

#ifndef __ConductrEnter__BaseScene__
#define __ConductrEnter__BaseScene__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "ofVideoPlayer.h"

class BaseScene : public ofxFadeScene
{
public:

    BaseScene(const string& name);

    void setup();

    // called when scene is entering, this is just a demo and this
    // implementation is not required for this class
    void updateEnter();

    // normal update
    void update();

    // called when scene is exiting, this is just a demo and this
    // implementation is not required for this class
    void updateExit();

    // draw
    void draw();

    // cleanup
    void exit();

    ofVideoPlayer videoPlayer;

protected:

    void enableAlphaBlendingForFade();
    void disableAlphaBlendingForFade();
};

#endif /* defined(__ConductrEnter__BaseScene__) */
