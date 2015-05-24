//
//  S4BaseObj.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4BaseObj__
#define __ConductrEnter__S4BaseObj__

#include <stdio.h>

#include "ofEasyCam.h"

class S4BaseObj
{
public:

    virtual ~S4BaseObj() {}

    void initialize(float _viewOriginX, float _viewWidth);

    virtual void setup() = 0;
    virtual void update() = 0;
    void draw(); // For testing purposes. This method must be pure virtual.

protected:

    ofEasyCam camera;
    float viewOriginX, viewWidth;
};

#endif /* defined(__ConductrEnter__S4BaseObj__) */
