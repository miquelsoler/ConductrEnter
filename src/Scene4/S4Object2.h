//
//  S4Object2.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4Object2__
#define __ConductrEnter__S4Object2__

#include <stdio.h>
#include "S4BaseObj.h"


class S4Object2 : public S4BaseObj
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
