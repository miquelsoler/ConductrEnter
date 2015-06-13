//
//  TUIOHandler.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 13/6/15.
//
//

#include "TUIOHandler.h"

#include "SettingsManager.h"

TUIOHandler::TUIOHandler()
{
    unsigned int clientPort = SettingsManager::getInstance().tuioClientPort;
    tuioClient.connect(clientPort);
}

void TUIOHandler::init()
{
    ofAddListener(ofEvents().touchDown, this, &TUIOHandler::tuioTouchDown);
    ofAddListener(ofEvents().touchUp, this, &TUIOHandler::tuioTouchUp);
    ofAddListener(ofEvents().touchMoved, this, &TUIOHandler::tuioTouchMoved);
}

void TUIOHandler::tuioTouchDown(ofTouchEventArgs &touch)
{
    ofNotifyEvent(eventTouchDown, touch, this);
//    cout << " cursor added: " + ofToString(touch.id)+
//    " X: "+ofToString(touch.x)+
//    " Y: "+ofToString(touch.y)
//    << endl;
}

void TUIOHandler::tuioTouchUp(ofTouchEventArgs &touch)
{
    ofNotifyEvent(eventTouchUp, touch, this);
//    cout << " cursor removed: " + ofToString(touch.id)+
//    " X: "+ofToString(touch.x)+
//    " Y: "+ofToString(touch.y)
//    << endl;
}

void TUIOHandler::tuioTouchMoved(ofTouchEventArgs &touch)
{
    ofNotifyEvent(eventTouchMoved, touch, this);
//    cout << " cursor updated: " + ofToString(touch.id)+
//    " X: "+ofToString(touch.x)+
//    " Y: "+ofToString(touch.y)
//    << endl;
}

void TUIOHandler::tuioPinched(ofTouchEventArgs &touch)
{

}
