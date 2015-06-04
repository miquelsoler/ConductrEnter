//
//  S3Object4.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Object4__
#define __ConductrEnter__S3Object4__

#include <stdio.h>
#include "S3BaseObj.h"

class S3Object4 : public S3BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

private:
    
};

#endif /* defined(__ConductrEnter__S4Object4__) */