//
//  S3Object3.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Object3__
#define __ConductrEnter__S3Object3__

#include <stdio.h>
#include "S3BaseObj.h"

class S3Object3 : public S3BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

private:
    
};

#endif /* defined(__ConductrEnter__S4Object3__) */
