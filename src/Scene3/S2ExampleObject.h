//
//  S2ExampleObject.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2ExampleObject__
#define __ConductrEnter__S2ExampleObject__

#include <stdio.h>
#include "S2BaseObj.h"
#include "of3dGraphics.h"

class S2ExampleObject : public S2BaseObj
{
public:
    S2ExampleObject(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void loadSettings();
    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void initInactive();
    void onCompleteInactive(float* arg);
    virtual void updateInactive();
    virtual void drawInactive();

    virtual void initTransitioning();
    void onCompleteTransitioning(float* arg);
    virtual void updateTransitioning();
    virtual void drawTransitioning();

    virtual void initActive();
    virtual void updateActive();
    virtual void drawActive();

    virtual void volumeChanged(float &newVolume);

    ofSpherePrimitive   sphere;
    float               sphereScale;
    ofColor             sphereColor;
};

#endif /* defined(__ConductrEnter__S2ExampleObject__) */
