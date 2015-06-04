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
    unsigned int fade_in_milliseconds;
    unsigned int fade_out_milliseconds;
    unsigned long scene4_timer_milliseconds;

    // OSC
    string oscAbletonHost;
    unsigned int oscAbletonPort;

private:

    SettingsManager();
    bool loadSettings();

    ofxJSONElement json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
