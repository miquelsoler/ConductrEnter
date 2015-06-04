//
//  S3Object2.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Object2__
#define __ConductrEnter__S3Object2__

#include <stdio.h>
#include "S3BaseObj.h"

class S3Object2 : public S3BaseObj
{
public:
    S3Object2(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

private:

};

#endif /* defined(__ConductrEnter__S4Object2__) */
