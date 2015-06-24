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
#include "TUIOReceiverEvent.h"

class TUIOHandler
{
public:
    static TUIOHandler &getInstance()
    {
        static TUIOHandler instance;
        return instance;
    }

    void init();
    void update();

    float getDistBetweenCursors(TuioCursor *cursor1, TuioCursor *cursor2);
    static ofVec2f tuioToScreenCoords(float tuioX, float tuioY);
    static ofVec2f screenToTuioCoords(float screenX, float screenY);

    TuioCursor *getCursorForId(int cursorId);

    ofxTuioClient               *tuioClient;
    ofxOscReceiver              tuioOscReceiver;

    ofEvent<ofTouchEventArgs>    eventTouchDown;
    ofEvent<ofTouchEventArgs>    eventTouchUp;
    ofEvent<ofTouchEventArgs>    eventTouchDrag;

    ofEvent<TUIOReceiverEvent>   eventTouchDownCursor;
    ofEvent<TUIOReceiverEvent>   eventTouchUpCursor;
    ofEvent<TUIOReceiverEvent>   eventTouchDragCursor;

private:

    TUIOHandler();

    void tuioTouchDown(ofTouchEventArgs &touch);
    void tuioTouchUp(ofTouchEventArgs &touch);
    void tuioTouchMoved(ofTouchEventArgs &touch);

    void tuioReceiverTouchDown(TUIOReceiverEvent &cursor);
    void tuioReceiverTouchUp(TUIOReceiverEvent &cursor);
    void tuioReceiverTouchMoved(TUIOReceiverEvent &cursor);
};

#endif /* defined(__ConductrEnter__TUIOHandler__) */
