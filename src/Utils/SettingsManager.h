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

    // Scene management
    unsigned int    sceneFirstScene;
    unsigned int    scene1IntroLoopFrame;
    unsigned int    sceneFadeInMilliseconds;
    unsigned int    sceneFadeOutMilliseconds;
    unsigned long   scene3TimerMilliseconds;

    // Ableton
    string          abletonHost;
    unsigned int    abletonSenderPort;
    unsigned int    abletonReceiverPort;
    unsigned int    abletonFirstClipIndex;
    unsigned int    abletonArtistOffset;

    // TUIO
    unsigned int    tuioClientPort;

    // Debug Mode
    bool            debugShowGUI;
    bool            debugShowTUIOCursors;

    // Pinch
    unsigned int    pinchCircleAlphaMin;
    unsigned int    pinchCircleAlphaMax;

private:

    SettingsManager();
    bool loadSettings();

    ofxJSONElement  json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
