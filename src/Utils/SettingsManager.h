//
//  SettingsManager.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 25/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__SettingsManager__
#define __ConductrEnter__SettingsManager__

#include <stdio.h>
#include "ofxJSON.h"

class SettingsManager
{
public:
    static SettingsManager &getInstance()
    {
        static SettingsManager instance;
        return instance;
    }

    // Displax
    unsigned int    displaxWidth;
    unsigned int    displaxHeight;

    // Scene management
    unsigned int    sceneFirstScene;
    unsigned int    scene1IntroLoopFrame;
    unsigned int    sceneFadeInMilliseconds;
    unsigned int    sceneFadeOutMilliseconds;
    unsigned long   scene2TimerMilliseconds;

    // Ableton
    string          abletonHost;
    unsigned int    abletonSenderPort;
    unsigned int    abletonReceiverPort;
    unsigned int    abletonFirstClipIndex;
    unsigned int    abletonArtistOffset;

    // TUIO Client
    unsigned int    tuioClientPort;

    // TUIO Server
    unsigned int    tuioServerPort;

    // Pinch
    unsigned int    pinchCircleAlphaMin;
    unsigned int    pinchCircleAlphaMax;

    // Debug Mode
    bool            debugShowGUI;
    bool            debugShowFPS;
    bool            debugShowTUIOCursors;
    bool            debugShowScene2BackgroundVideo;

    // Release Mode
    bool            releaseShowGUI;
    bool            releaseShowFPS;
    bool            releaseShowTUIOCursors;
    bool            releaseShowScene2BackgroundVideo;

private:

    SettingsManager();
    bool loadSettings();

    ofxJSONElement  json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
