//
//  AbletonManager.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 10/6/15.
//
//

#pragma once

#ifndef __ConductrEnter__AbletonManager__
#define __ConductrEnter__AbletonManager__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

class AbletonManager
{
public:
    AbletonManager() {};
    AbletonManager(string _senderHost, unsigned int _senderPort, unsigned int _receiverPort);

    void playClip(int clipNumber, int trackNumber);
    void stopClip(int clipNumber, int trackNumber);
    void stopAll();

    void setDeviceParameter(int device, int parameter, int value);

private:
    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;

    string senderHost;
    unsigned int senderPort;
    unsigned int receiverPort;
};


#endif /* defined(__ConductrEnter__AbletonListener__) */
