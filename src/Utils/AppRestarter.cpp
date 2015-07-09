//
//  AppRestart.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 9/7/15.
//
//

#include "AppRestarter.h"


///--------------------------------------------------------------
AppRestarter::AppRestarter()
{
    isWaitingToRestart = false;
    isRestarting = false;
    elapsedTime = 0;
    startTime = 0;
    countdown = 0;
}

///--------------------------------------------------------------
AppRestarter::~AppRestarter()
{
    ofRemoveListener(ofEvents().update, this, &AppRestarter::update);
    ofRemoveListener(ofEvents().draw, this, &AppRestarter::draw);
}

///--------------------------------------------------------------
void AppRestarter::restart(float _delay, bool showRestartMessage)
{
    startTime = ofGetElapsedTimef();
    isWaitingToRestart = true;
    delay = _delay;
    showMessage = showRestartMessage;

    ofAddListener(ofEvents().update, this, &AppRestarter::update);
    ofAddListener(ofEvents().draw, this, &AppRestarter::draw);
}

///--------------------------------------------------------------
void AppRestarter::update(ofEventArgs &event)
{
    if (isWaitingToRestart)
    {
        elapsedTime = ofGetElapsedTimef() - startTime;
        countdown = delay - elapsedTime;
        if ((countdown < 0) && !isRestarting)
        {
            doRestart();
            isRestarting = true;
        }
    }
}

///--------------------------------------------------------------
void AppRestarter::draw(ofEventArgs &event)
{
    if (isWaitingToRestart && showMessage)
    {
        string message = "Restarting in " + ofToString(int(countdown)) + " seconds...";
        ofSetColor(ofColor::green);
        ofDrawBitmapString(message, 130, ofGetHeight()-15);
    }
}

///--------------------------------------------------------------
void AppRestarter::doRestart()
{
    ofSystem("open " + getAppPath());
    ofExit();
}

///--------------------------------------------------------------
string AppRestarter::getAppPath()
{
    string appPath = ofFilePath::getAbsolutePath(ofFilePath::getCurrentExePath());
    return appPath;
}

