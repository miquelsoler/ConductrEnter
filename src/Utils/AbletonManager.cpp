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

AbletonManager::AbletonManager(string _senderHost, unsigned int _senderPort, unsigned int _receiverPort, unsigned int numObjects)
{
    senderHost = _senderHost;
    senderPort = _senderPort;
    receiverPort = _receiverPort;

    sceneNumObjects = numObjects;

    oscSender.setup(senderHost, senderPort);
    oscReceiver.setup(receiverPort);

//    for (int i=0; i<sceneNumObjects; i++) {
//        ofEvent<float> event;
//        eventsVolumeChanged.push_back(&event);
//    }
}

#pragma mark - Send messages

/**
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

/**
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

/**
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


/**
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
//    cout << "Message: " << m.getAddress() << "-" << device << "-" << parameter << "-" << value << endl;
#endif
}

/**
 * /live/tempo
 * Request current tempo, replies with /live/tempo (float tempo)
 */
void AbletonManager::requestTempo()
{
    ofxOscMessage m;
    m.setAddress("/live/tempo");
    oscSender.sendMessage(m);
}



/**
 * /live/volumeupdates (int window, int min_track, int max_track
 * Request volume updates
 */
void AbletonManager::requestVolumeUpdates()
{
    ofxOscMessage m;
    m.setAddress("/live/volumeupdates");
    m.addIntArg(0); // window
    m.addIntArg(0); // min_track
    m.addIntArg(8); // max_track
    
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
            manageTempoChanged(m);
        else if (m.getAddress() == "/live/track/meterblock")
            manageTracksVolumeChanged(m);
        else if (m.getAddress() == "/live/master/meterblock")
            manageMasterVolumeChanged(m);
    }
}

void AbletonManager::manageTempoChanged(ofxOscMessage &m)
{
    /**
     * Response for tempo changes:
     * /live/tempo
     * (float) tempo
     */
    float newTempo = m.getArgAsFloat(0);
    ofNotifyEvent(eventTempoChanged, newTempo, this);
}

void AbletonManager::manageTracksVolumeChanged(ofxOscMessage &m)
{
    /**
     * Response for track volume (amplitude) changes:
     * /live/track/meterblock
     * N triplets with:
     *   (int) track number
     *   (int) channel (0=left, 1=right)
     *   (float) volume (0..1)
     */

    int track, channel;
    float volume;

    int numArgs = m.getNumArgs();
    for (int i=0; i<numArgs; i+=3)
    {
        track = m.getArgAsInt32(i);
        channel = m.getArgAsInt32(i+1);
        volume = m.getArgAsFloat(i+2);

        if (channel == 1) continue; // Skip right channel messages
        if (track >= sceneNumObjects) continue; // Skip if this track index is larger than the number of objects in scene

//        cout << " " << track << " " << channel << " " << volume << " - ";

        //        ofMap(volume, 0.4, 1, 0, 1);

        switch(track)
        {
            case 0: ofNotifyEvent(eventVolumeChanged0, volume, this); break;
            case 1: ofNotifyEvent(eventVolumeChanged1, volume, this); break;
            case 2: ofNotifyEvent(eventVolumeChanged2, volume, this); break;
            case 3: ofNotifyEvent(eventVolumeChanged3, volume, this); break;
            case 4: ofNotifyEvent(eventVolumeChanged4, volume, this); break;
            case 5: ofNotifyEvent(eventVolumeChanged5, volume, this); break;
            default: break;
        }
    }
//    cout << endl;
}

void AbletonManager::manageMasterVolumeChanged(ofxOscMessage &m)
{
    /**
     * Response for master volume (amplitude) changes:
     * /live/master/meterblock
     * (int) channel (0=left, 1=right)
     * (float) volume (0..1)
     */
}
