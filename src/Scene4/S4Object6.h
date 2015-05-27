//
//  S4Object6.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4Object6__
#define __ConductrEnter__S4Object6__

#include <stdio.h>
#include "S4BaseObj.h"

class S4Object6 : public S4BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();
};

#endif /* defined(__ConductrEnter__S4Object6__) */
