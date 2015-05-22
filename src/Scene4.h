//
//  Scene4.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

#ifndef __ConductrEnter__Scene4__
#define __ConductrEnter__Scene4__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "BaseScene.h"

class Scene4 : public BaseScene
{
public:

    Scene4(const string& name) : BaseScene(name) {}

    void setup();
    void update();
    void draw();
    void exit();
};

#endif /* defined(__ConductrEnter__Scene4__) */
