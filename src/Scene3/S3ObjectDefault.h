//
//  S3ObjectDefault.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3ObjectDefault__
#define __ConductrEnter__S3ObjectDefault__

#include <stdio.h>
#include "S3BaseObj.h"
#include "of3dGraphics.h"

class S3ObjectDefault : public S3BaseObj
{
public:
    S3ObjectDefault(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void updateInactive();
    virtual void updateTransitioning();
    virtual void updateActive();
    virtual void drawInactive();
    virtual void drawTransitioning();
    virtual void drawActive();

    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    void updateRotation();

    virtual void volumeChanged(float &newVolume) {};

    ofSpherePrimitive   sphere;
    float               initialRotation;
};

#endif /* defined(__ConductrEnter__S3ObjectDefault__) */
