//
//  Scene1.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 21/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__Scene1__
#define __ConductrEnter__Scene1__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "BaseScene.h"
#include "of3dPrimitives.h"


class Scene1 : public BaseScene
{
public:

    Scene1(const string& name) : BaseScene(name) {}

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

#endif /* defined(__ConductrEnter__Scene1__) */
