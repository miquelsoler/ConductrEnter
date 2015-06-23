//
//  TUIOHandler.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 13/6/15.
//
//

#pragma once

#ifndef __ConductrEnter__TUIOHandler__
#define __ConductrEnter__TUIOHandler__

#include <stdio.h>
#include "ofMain.h"
#include "ofxTuioClient.h"
#include "TuioCursor.h"
#include "ofxOsc.h"

class TUIOHandler
{
public:
    static TUIOHandler &getInstance()
    {
        static TUIOHandler instance;
        return instance;
    }

    void init();
//    void update();

    float getDistBetweenCursors(int cursorId1, int cursorId2);
    static ofVec2f tuioToScreenCoords(float tuioX, float tuioY);

    TuioCursor *getCursorForId(int cursorId);

    ofxTuioClient               *tuioClientLocal;
    ofxTuioClient               *tuioClientRemote;

    ofEvent<ofTouchEventArgs>    eventTouchDown;
    ofEvent<ofTouchEventArgs>    eventTouchUp;
    ofEvent<ofTouchEventArgs>    eventTouchDrag;

private:

    TUIOHandler();

    void tuioTouchDown(ofTouchEventArgs &touch);
    void tuioTouchUp(ofTouchEventArgs &touch);
    void tuioTouchMoved(ofTouchEventArgs &touch);
};

#endif /* defined(__ConductrEnter__TUIOHandler__) */
