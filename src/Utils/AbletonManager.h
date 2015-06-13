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
    AbletonManager(string _senderHost, unsigned int _senderPort, unsigned int _receiverPort, unsigned int numObjects);
    virtual ~AbletonManager();

    void playClip(int clipNumber, int trackNumber);
    void stopClip(int clipNumber, int trackNumber);
    void stopAll();

    void setDeviceParameter(int device, int parameter, int value);

    void requestTempo();
    void requestVolumeUpdates();

    void update();

    ofEvent<float> eventTempoChanged;
    vector< ofEvent<float> > eventsVolumeChanged;

private:

    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;

    unsigned int sceneNumObjects;

    string senderHost;
    unsigned int senderPort;
    unsigned int receiverPort;

    void manageTempoChanged(ofxOscMessage &m);
    void manageTracksVolumeChanged(ofxOscMessage &m);
    void manageMasterVolumeChanged(ofxOscMessage &m);
};


#endif /* defined(__ConductrEnter__AbletonListener__) */
