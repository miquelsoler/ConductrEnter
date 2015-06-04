//
//  S3Object1.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Object1__
#define __ConductrEnter__S3Object1__

#include <stdio.h>
#include "S3BaseObj.h"
#include "of3dGraphics.h"

class S3Object1 : public S3BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

    virtual void setY(float newY);

private:

    void updateRotation();

    ofSpherePrimitive sphere;
    float initialRotation;
};

#endif /* defined(__ConductrEnter__S4Object1__) */
