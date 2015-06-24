//
//  TUIOReceiverEvent.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 23/6/15.
//
//

#pragma once

#ifndef __ConductrEnter__TUIOReceiverEvent__
#define __ConductrEnter__TUIOReceiverEvent__

#include <stdio.h>
#include "ofMain.h"

class TUIOReceiverEvent : public ofEventArgs
{
public:

    int     sourceId;
    int     sessionId;
    int     cursorId;
    float   x;
    float   y;
    float   xSpeed;
    float   ySpeed;
    float   motionAccel;

    TUIOReceiverEvent() {};

    static ofEvent<TUIOReceiverEvent> event;
};

#endif /* defined(__ConductrEnter__TUIOReceiverEvent__) */
