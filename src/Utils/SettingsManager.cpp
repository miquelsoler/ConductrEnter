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

    string prefix;

    // Displax
    prefix = "Displax";
    displaxWidth = json[prefix]["Screen Width"].asUInt();
    displaxHeight = json[prefix]["Screen Height"].asUInt();

    // Scene management
    prefix = "Scenes";
    sceneFirstScene = json[prefix]["First Scene"].asUInt();
    scene1IntroLoopFrame = json[prefix]["Scene1 Intro Loop Frame"].asUInt();
    sceneFadeInMilliseconds = json[prefix]["FadeIn Milliseconds"].asUInt();
    sceneFadeOutMilliseconds = json[prefix]["FadeOut Milliseconds"].asUInt();
    scene3TimerMilliseconds = json[prefix]["Scene2 Timer Milliseconds"].asUInt();

    // Ableton
    prefix = "Ableton";
    abletonHost = json[prefix]["Ableton Host"].asString();
    abletonSenderPort = json[prefix]["Ableton Sender Port"].asUInt();
    abletonReceiverPort = json[prefix]["Ableton Receiver Port"].asUInt();
    abletonFirstClipIndex = json[prefix]["First Clip Index"].asUInt();
    abletonArtistOffset = json[prefix]["Artist Offset"].asUInt();

    // TUIO Client
    prefix = "TUIO Client";
    tuioClientPort = json[prefix]["Client Port"].asUInt();

    // TUIO Server
    prefix = "TUIO Server";
    tuioServerPort = json[prefix]["Client Port"].asUInt();

    // Pinch
    prefix = "Pinch";
    pinchCircleAlphaMin = json[prefix]["Circle Alpha Min"].asUInt();
    pinchCircleAlphaMax = json[prefix]["Circle Alpha Max"].asUInt();

    // Debug Mode
    prefix = "Debug Mode";
    debugShowGUI = json[prefix]["Show GUI"].asBool();
    debugShowFPS = json[prefix]["Show FPS"].asBool();
    debugShowTUIOCursors = json[prefix]["Show TUIO Cursors"].asBool();
    debugShowScene2BackgroundVideo = json[prefix]["Show Scene2 Background Video"].asBool();

    // Release mode
    prefix = "Release Mode";
    releaseShowGUI = json[prefix]["Show GUI"].asBool();
    releaseShowFPS = json[prefix]["Show FPS"].asBool();
    releaseShowTUIOCursors = json[prefix]["Show TUIO Cursors"].asBool();
    releaseShowScene2BackgroundVideo = json[prefix]["Show Scene2 Background Video"].asBool();

    return parsingSuccessful;
}
