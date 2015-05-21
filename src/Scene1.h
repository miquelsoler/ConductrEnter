//
//  Scene1.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

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
    void draw();

    ofSpherePrimitive sphere;
};

#endif /* defined(__ConductrEnter__Scene1__) */
