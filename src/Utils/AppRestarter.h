//
//  AppRestart.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 9/7/15.
//
//

#pragma once

#ifndef __ConductrEnter__AppRestart__
#define __ConductrEnter__AppRestart__

#include <stdio.h>
#include "ofMain.h"

class AppRestarter
{
public:

    AppRestarter();
    ~AppRestarter();

    void restart(float delay=0, bool showRestartMessage = true);

private:

    void update(ofEventArgs &event);
    void draw(ofEventArgs &event);

    void doRestart();

    string getAppPath();

    float delay;
    float countdown;
    float elapsedTime;
    float startTime;

    bool showMessage;
    bool isRestarting;
    bool isWaitingToRestart;
};

#endif /* defined(__ConductrEnter__AppRestart__) */
