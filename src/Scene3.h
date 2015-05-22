//
//  Scene3.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#ifndef __ConductrEnter__Scene3__
#define __ConductrEnter__Scene3__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "BaseScene.h"

class Scene3 : public BaseScene
{
public:

    Scene3(const string& name) : BaseScene(name) {}

    void setup();
    void update();
    virtual void drawScene();
    void exit();
};

#endif /* defined(__ConductrEnter__Scene3__) */
