//
//  S4Object3.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4Object3__
#define __ConductrEnter__S4Object3__

#include <stdio.h>
#include "S4BaseObj.h"

class S4Object3 : public S4BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

private:

    // Loop arc
    ofPolyline loopArc;
    float loopRadius;
    float loopTimePerCycle;
    unsigned int loopFrequency;
};

#endif /* defined(__ConductrEnter__S4Object3__) */