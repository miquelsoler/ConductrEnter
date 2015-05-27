//
//  S4Object1.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4Object1__
#define __ConductrEnter__S4Object1__

#include <stdio.h>
#include "S4BaseObj.h"
#include "of3dGraphics.h"

class S4Object1 : public S4BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

private:

    ofSpherePrimitive sphere;
    float initialRotation;
};

#endif /* defined(__ConductrEnter__S4Object1__) */
