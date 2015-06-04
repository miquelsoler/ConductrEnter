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

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

//    virtual void setY(float newY) {};

private:

};

#endif /* defined(__ConductrEnter__S4Object2__) */
