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
#include "ofMain.h"

class S4BaseObj
{
public:

    virtual ~S4BaseObj() {}

    void initialize(float _viewOriginX, float _viewWidth);

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    void displaySettings();

protected:

    ofEasyCam camera;
    ofRectangle viewRectangle;
    float viewOriginX, viewWidth;
};

#endif /* defined(__ConductrEnter__S4BaseObj__) */
