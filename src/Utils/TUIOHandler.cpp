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
    unsigned int clientLocalPort = SettingsManager::getInstance().tuioClientLocalPort;
    tuioClientLocal = new ofxTuioClient();
    tuioClientLocal->connect(clientLocalPort);

    unsigned int clientRemotePort = SettingsManager::getInstance().tuioClientRemotePort;
    tuioClientRemote = new ofxTuioClient();
    tuioClientRemote->connect(clientRemotePort);
}

///--------------------------------------------------------------
void TUIOHandler::init()
{
    ofAddListener(ofEvents().touchDown, this, &TUIOHandler::tuioTouchDown);
    ofAddListener(ofEvents().touchUp, this, &TUIOHandler::tuioTouchUp);
    ofAddListener(ofEvents().touchMoved, this, &TUIOHandler::tuioTouchMoved);
}

/////--------------------------------------------------------------
//void TUIOHandler::update()
//{
////    while(oscReceiver.hasWaitingMessages())
////    {
////        ofxOscMessage m;
////        oscReceiver.getNextMessage(&m);
////
////        ofTouchEventArgs touch;
//////        TuioCursor (long si, int ci, float xp, float yp);
////
//////        TuioCursor cursor();
//////        tuioClientLocal->addTuioCursor(<#(TuioCursor*)tcur#>);
////        touch.set(m.getArgAsFloat(0), m.getArgAsFloat(1));
////        touch.id = m.getArgAsInt32(2);
////        if (m.getAddress() == "/server/tuio/touchdown")
////            tuioTouchDown(touch);
////        else if (m.getAddress() == "/server/tuio/touchup")
////            tuioTouchUp(touch);
////        else if (m.getAddress() == "/server/tuio/drag")
////            tuioTouchMoved(touch);
////    }
//}

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
float TUIOHandler::getDistBetweenCursors(int cursorId1, int cursorId2)
{
    TuioCursor *c1 = tuioClientLocal->client->getTuioCursor(cursorId1);
    TuioCursor *c2 = tuioClientLocal->client->getTuioCursor(cursorId2);

    if ((c1 == NULL) || (c2 == NULL)) return 0;

    ofVec2f screenC1 = TUIOHandler::tuioToScreenCoords(c1->getPosition().getX(), c1->getPosition().getY());
    ofVec2f screenC2 = TUIOHandler::tuioToScreenCoords(c2->getPosition().getX(), c2->getPosition().getY());

    return ofDist(screenC1.x, screenC1.y, screenC2.x, screenC2.y);
}

///--------------------------------------------------------------
ofVec2f TUIOHandler::tuioToScreenCoords(float tuioX, float tuioY)
{
    ofVec2f screenCoords(ofMap(tuioX, 0, 1, 0, ofGetWidth()),
                         ofMap(tuioY, 0, 1, 0, ofGetHeight()));
    return screenCoords;
}

///--------------------------------------------------------------
TuioCursor *TUIOHandler::getCursorForId(int cursorId)
{
    TuioCursor *cursor = tuioClientLocal->client->getTuioCursor(cursorId);
    if (cursor == NULL)
    {
        cursor = tuioClientRemote->client->getTuioCursor(cursorId);
    }
    return cursor;
}
