//
//  S3Object6.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Object6__
#define __ConductrEnter__S3Object6__

#include <stdio.h>
#include "S3BaseObj.h"

class S3Object6 : public S3BaseObj
{
public:
    S3Object6(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

private:

    virtual void volumeChanged(float &newVolume) {};
};

#endif /* defined(__ConductrEnter__S4Object6__) */
