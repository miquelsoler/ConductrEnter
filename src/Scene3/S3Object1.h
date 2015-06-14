//
//  S3Object1.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
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
    S3Object1(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY) {};

private:

    void updateRotation();

    virtual void volumeChanged(float &newVolume) {};
    virtual void windowResized(ofResizeEventArgs &args);

    ofSpherePrimitive sphere;
    float initialRotation;
};

#endif /* defined(__ConductrEnter__S4Object1__) */
