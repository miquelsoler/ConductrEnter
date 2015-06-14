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
    virtual void tuioPressed(ofVec2f &coords);
    virtual void tuioReleased(ofVec2f &coords);
    virtual void tuioDragged(ofVec2f &coords);

    // Mouse events
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);

    // Interaction handling
    void handlePress(int x, int y);
    void handleRelease(int x, int y);
    void handleDrag(int x, int y);

    /**/ // OSC
    int getObjectIndexAtPosition(int x, int y);
    AbletonManager *abletonManager;

    ofxOscSender oscSender;

    // Listener method to detect window changes
    virtual void windowResized(ofResizeEventArgs &args);

    // Listener method to detect tempo changes
    virtual void tempoChanged(float &newTempo);

    vector<S3BaseObj*> objects;
    unsigned int num_objects;
    float viewWidth, viewHeight;
};

#endif /* defined(__ConductrEnter__Scene4__) */
