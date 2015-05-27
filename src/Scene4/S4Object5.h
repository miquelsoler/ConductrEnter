//
//  S4Object5.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4Object5__
#define __ConductrEnter__S4Object5__

#include <stdio.h>
#include "S4BaseObj.h"

class S4Object5 : public S4BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();
};

#endif /* defined(__ConductrEnter__S4Object5__) */
