//
//  AbletonManager.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 10/6/15.
//
//

#include "AbletonManager.h"

const unsigned int MAX_TRACKS = 20;

#pragma mark - Constructors

AbletonManager::AbletonManager(string _senderHost, unsigned int _senderPort, unsigned int _receiverPort)
{
    senderHost = _senderHost;
    senderPort = _senderPort;
    receiverPort = _receiverPort;

    oscSender.setup(senderHost, senderPort);
    oscReceiver.setup(receiverPort);
}

#pragma mark - Send messages

/*
 * /live/play/clip
 * (int track, int clip)
 * Launches clip number clip in track number track
 */
void AbletonManager::playClip(int clipNumber, int trackNumber)
{
    ofxOscMessage m;
    m.setAddress("/live/play/clip");
    m.addIntArg(trackNumber); // Session view -> col number (track)
    m.addIntArg(clipNumber); // Session view -> row number (clip)
    oscSender.sendMessage(m);
}

/*
 * /live/stop/clip
 * (int track, int clip)
 * Stops clip number clip in track number track
 */
void AbletonManager::stopClip(int clipNumber, int trackNumber)
{
    ofxOscMessage m;
    m.setAddress("/live/stop/clip");
    m.addIntArg(trackNumber); // Session view -> col number (track)
    m.addIntArg(clipNumber); // Session view -> row number (clip)
    oscSender.sendMessage(m);
}

/*
 * /live/stop/track
 * (int track)
 * Stops track number track
 */
void AbletonManager::stopAll()
{
    for (unsigned int i=0; i<MAX_TRACKS; i++) {
        ofxOscMessage m;
        m.setAddress("/live/stop/track");
        m.addIntArg(i);
        oscSender.sendMessage(m);
    }
}


/*
 * /live/master/device
 * (int device, int parameter, int value)
 * Sets parameter on device on track number track to value
 */
void AbletonManager::setDeviceParameter(int device, int parameter, int value)
{
    ofxOscMessage m;
    m.setAddress("/live/master/device");
    m.addIntArg(device);
    m.addIntArg(parameter);
    m.addIntArg(value);
    oscSender.sendMessage(m);
#ifdef OF_DEBUG
    cout << "Message: " << m.getAddress() << "-" << device << "-" << parameter << "-" << value << endl;
#endif
}

/*
 * /live/tempo
 * Request current tempo, replies with /live/tempo (float tempo)
 */
void AbletonManager::requestTempo()
{
    ofxOscMessage m;
    m.setAddress("/live/tempo");
    oscSender.sendMessage(m);
}

#pragma mark - Receive messages

void AbletonManager::update()
{
    while(oscReceiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        oscReceiver.getNextMessage(&m);

        if (m.getAddress() == "/live/tempo")
        {
            float newTempo = m.getArgAsFloat(0);
            ofNotifyEvent(tempoChanged, newTempo, this);
        }
    }
}
