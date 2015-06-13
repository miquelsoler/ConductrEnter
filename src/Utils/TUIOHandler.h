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

class TUIOHandler
{
public:
    static TUIOHandler &getInstance()
    {
        static TUIOHandler instance;
        return instance;
    }

    void init();

    ofxTuioClient tuioClient;

    ofEvent<ofVec2f> eventTouchUp;
    ofEvent<ofVec2f> eventTouchDown;
    ofEvent<ofVec2f> eventTouchMoved;

private:

    TUIOHandler();

    void tuioTouchDown(ofTouchEventArgs &touch);
    void tuioTouchUp(ofTouchEventArgs &touch);
    void tuioTouchMoved(ofTouchEventArgs &touch);
    void tuioPinched(ofTouchEventArgs &touch);
};

#endif /* defined(__ConductrEnter__TUIOHandler__) */
