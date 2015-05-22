//
//  BaseScene.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 21/5/15.
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
//    virtual void drawScene() = 0; // Classe �s pura, no es pot instanciar i totes les subclasses han de redefinir aquest m�tode
    virtual void drawScene() {} // Classe no pura, es pot instanciar, i no cal redefinir m�tode

    // cleanup
    void exit();

    ofVideoPlayer videoPlayer;
};

#endif /* defined(__ConductrEnter__BaseScene__) */
