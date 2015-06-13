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
    unsigned int intro_loop_frame;
    unsigned int fade_in_milliseconds;
    unsigned int fade_out_milliseconds;
    unsigned long scene4_timer_milliseconds;

    // Ableton
    string abletonHost;
    unsigned int abletonSenderPort;
    unsigned int abletonReceiverPort;
    unsigned int abletonFirstClipIndex;
    unsigned int abletonArtistOffset;

    // TUIO
    unsigned int tuioClientPort;

private:

    SettingsManager();
    bool loadSettings();

    ofxJSONElement json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
