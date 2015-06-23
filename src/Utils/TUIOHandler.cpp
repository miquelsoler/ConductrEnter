//
//  TUIOHandler.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 13/6/15.
//
//

#include "TUIOHandler.h"

#include "SettingsManager.h"

///--------------------------------------------------------------
TUIOHandler::TUIOHandler()
{
    unsigned int clientPort = SettingsManager::getInstance().tuioClientPort;
    tuioClient = new ofxTuioClient();
    tuioClient->connect(clientPort);

    tuioOscReceiver.setup(SettingsManager::getInstance().tuioServerPort);
}

///--------------------------------------------------------------
void TUIOHandler::init()
{
    ofAddListener(ofEvents().touchDown, this, &TUIOHandler::tuioTouchDown);
    ofAddListener(ofEvents().touchUp, this, &TUIOHandler::tuioTouchUp);
    ofAddListener(ofEvents().touchMoved, this, &TUIOHandler::tuioTouchMoved);
}

///--------------------------------------------------------------
void TUIOHandler::update()
{
    while(tuioOscReceiver.hasWaitingMessages())
    {
        ofxOscMessage m;

        tuioOscReceiver.getNextMessage(&m);

        TUIOReceiverEvent cursor;
        cursor.sourceId = m.getArgAsInt32(0);
        cursor.sessionId = m.getArgAsInt32(1);
        cursor.cursorId = m.getArgAsInt32(2);
        cursor.x = m.getArgAsFloat(3);
        cursor.y = m.getArgAsFloat(4);
        cursor.xSpeed = m.getArgAsFloat(5);
        cursor.ySpeed = m.getArgAsFloat(6);
        cursor.motionAccel = m.getArgAsFloat(7);

        if (m.getAddress() == "/tuio/touchdown")
            tuioReceiverTouchDown(cursor);
        else if (m.getAddress() == "/tuio/touchup")
            tuioReceiverTouchUp(cursor);
        else if (m.getAddress() == "/tuio/drag")
            tuioReceiverTouchMoved(cursor);
    }
}

///--------------------------------------------------------------
void TUIOHandler::tuioTouchDown(ofTouchEventArgs &touch)
{
    ofNotifyEvent(eventTouchDown, touch, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioTouchUp(ofTouchEventArgs &touch)
{
    ofNotifyEvent(eventTouchUp, touch, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioTouchMoved(ofTouchEventArgs &touch)
{
    ofNotifyEvent(eventTouchDrag, touch, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioReceiverTouchDown(TUIOReceiverEvent &cursor)
{
    ofNotifyEvent(eventTouchDownCursor, cursor, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioReceiverTouchUp(TUIOReceiverEvent &cursor)
{
    ofNotifyEvent(eventTouchUpCursor, cursor, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioReceiverTouchMoved(TUIOReceiverEvent &cursor)
{
    ofNotifyEvent(eventTouchDragCursor, cursor, this);
}

///--------------------------------------------------------------
float TUIOHandler::getDistBetweenCursors(TuioCursor *cursor1, TuioCursor *cursor2)
{
    if ((cursor1 == NULL) || (cursor2 == NULL)) return 0;

    ofVec2f screenC1 = TUIOHandler::tuioToScreenCoords(cursor1->getPosition().getX(), cursor1->getPosition().getY());
    ofVec2f screenC2 = TUIOHandler::tuioToScreenCoords(cursor2->getPosition().getX(), cursor2->getPosition().getY());

    float distance = ofDist(screenC1.x, screenC1.y, screenC2.x, screenC2.y);
    return distance;
}

///--------------------------------------------------------------
ofVec2f TUIOHandler::tuioToScreenCoords(float tuioX, float tuioY)
{
    ofVec2f screenCoords(ofMap(tuioX, 0, 1, 0, ofGetWidth()),
                         ofMap(tuioY, 0, 1, 0, ofGetHeight()));
    return screenCoords;
}

///--------------------------------------------------------------
ofVec2f TUIOHandler::screenToTuioCoords(float screenX, float screenY)
{
    ofVec2f tuioCoords(ofMap(screenX, 0, ofGetWidth(), 0, 1),
                         ofMap(screenY, 0, ofGetHeight(), 0, 1));
    return tuioCoords;
}

///--------------------------------------------------------------
TuioCursor *TUIOHandler::getCursorForId(int cursorId)
{
    TuioCursor *cursor = tuioClient->client->getTuioCursor(cursorId);
    return cursor;
}
