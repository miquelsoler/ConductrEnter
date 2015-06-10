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
#include "BaseScene.h"
#include "OrthoCamera.h"

class Scene2 : public BaseScene
{
public:

    Scene2(const string& name, bool singleSetup) : BaseScene(name, singleSetup) {}

    void setup();
    void update();
    void draw();
    void exit();

private:
    
    // Touch (currently mouse) events
    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
};

#endif /* defined(__ConductrEnter__Scene2__) */
