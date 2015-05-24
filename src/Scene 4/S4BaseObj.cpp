//
//  S4BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S4BaseObj.h"

void S4BaseObj::initialize(float _viewOriginX, float _viewWidth)
{
    viewOriginX = _viewOriginX;
    viewWidth = _viewWidth;
}

// For testing purposes. This method must be pure virtual.
void S4BaseObj::draw()
{
    ofCircle(viewOriginX+(viewWidth/2), ofGetHeight()/2, 30);
}
