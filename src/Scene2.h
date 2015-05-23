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
#include <ofxAppUtils.h>
#include "BaseScene.h"

class Scene2 : public BaseScene
{
public:

    Scene2(const string& name) : BaseScene(name) {}

    void setup();
    void update();
    virtual void drawScene();
    void exit();

    ofSpherePrimitive sphere;
};

#endif /* defined(__ConductrEnter__Scene2__) */
