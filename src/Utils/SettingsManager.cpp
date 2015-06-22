//
//  SettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 25/5/15.
//
//

#include "SettingsManager.h"

const std::string FILENAME = "settings/settings.json";

///--------------------------------------------------------------
SettingsManager::SettingsManager()
{
    bool parserResult = loadSettings();
    if (!parserResult)
    {
        ofLog(OF_LOG_ERROR, "BAD FORMAT IN settings.json. Now quitting...");
        std::exit(EXIT_FAILURE);
    }
}

///--------------------------------------------------------------
bool SettingsManager::loadSettings()
{
    // JSON parse

    bool parsingSuccessful = json.open(FILENAME);
#ifdef OF_DEBUG
    cout << "PARSING RESULT: " << parsingSuccessful << endl;
#endif

    // Scene management
    sceneFirstScene = json["Scenes"]["First Scene"].asUInt();
    scene1IntroLoopFrame = json["Scenes"]["Scene1 Intro Loop Frame"].asUInt();
    sceneFadeInMilliseconds = json["Scenes"]["FadeIn Milliseconds"].asUInt();
    sceneFadeOutMilliseconds = json["Scenes"]["FadeOut Milliseconds"].asUInt();
    scene3TimerMilliseconds = json["Scenes"]["Scene3 Timer Milliseconds"].asUInt();

    // Ableton
    abletonHost = json["Ableton"]["Ableton Host"].asString();
    abletonSenderPort = json["Ableton"]["Ableton Sender Port"].asUInt();
    abletonReceiverPort = json["Ableton"]["Ableton Receiver Port"].asUInt();
    abletonFirstClipIndex = json["Ableton"]["First Clip Index"].asUInt();
    abletonArtistOffset = json["Ableton"]["Artist Offset"].asUInt();

    // TUIO
    tuioClientPort = json["TUIO"]["Client Port"].asUInt();

    // Debug Mode
    debugShowGUI = json["Debug Mode"]["Show GUI"].asBool();
    debugShowTUIOCursors = json["Debug Mode"]["Show TUIO Cursors"].asBool();

    // Pinch
    pinchCircleAlphaMin = json["Pinch"]["Circle Alpha Min"].asUInt();
    pinchCircleAlphaMax = json["Pinch"]["Circle Alpha Max"].asUInt();

    // TUIO Server
    tuioServerReceiverPort = json["TUIO Server"]["Receiver Port"].asUInt();

    return parsingSuccessful;
}
