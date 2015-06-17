//
//  S3NoiseSphere.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3NoiseSphere__
#define __ConductrEnter__S3NoiseSphere__

#include <stdio.h>
#include "S3BaseObj.h"

class S3NoiseSphere : public S3BaseObj
{
public:
    S3NoiseSphere(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void volumeChanged(float &newVolume) {};
};

#endif /* defined(__ConductrEnter__S3NoiseSphere__) */
