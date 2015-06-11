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

    void requestTempo();
    void requestVolumeUpdates();

    void update();

    ofEvent<float> tempoChanged;
    ofEvent<float> volumeChanged0;
    ofEvent<float> volumeChanged1;
    ofEvent<float> volumeChanged2;
    ofEvent<float> volumeChanged3;
    ofEvent<float> volumeChanged4;
    ofEvent<float> volumeChanged5;

private:

    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;

    string senderHost;
    unsigned int senderPort;
    unsigned int receiverPort;

    void manageTempoChanged(ofxOscMessage &m);
    void manageTracksVolumeChanged(ofxOscMessage &m);
    void manageMasterVolumeChanged(ofxOscMessage &m);
};


#endif /* defined(__ConductrEnter__AbletonListener__) */
