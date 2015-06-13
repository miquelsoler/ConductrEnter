//
//  SettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 25/5/15.
//
//

#include "SettingsManager.h"

#include "ofLog.h"

const std::string FILENAME = "settings/settings.json";

SettingsManager::SettingsManager()
{
    bool parserResult = loadSettings();
    if (!parserResult)
    {
        ofLog(OF_LOG_ERROR, "BAD FORMAT IN settings.json. Now quitting...");
        std::exit(EXIT_FAILURE);
    }
}

bool SettingsManager::loadSettings()
{
    // JSON parse

    bool parsingSuccessful = json.open(FILENAME);
#ifdef OF_DEBUG
    cout << "PARSING RESULT: " << parsingSuccessful << endl;
#endif

    // Scene management
    intro_loop_frame = json["Scenes"]["Intro Loop Frame"].asUInt();
    fade_in_milliseconds = json["Scenes"]["FadeIn Milliseconds"].asUInt();
    fade_out_milliseconds = json["Scenes"]["FadeOut Milliseconds"].asUInt();
    scene4_timer_milliseconds = json["Scenes"]["Scene4 Timer Milliseconds"].asUInt();
#ifdef OF_DEBUG
    cout << "[Scenes] fadeIn=" << fade_in_milliseconds << " fadeOut=" << fade_out_milliseconds << " scene4Timer=" << scene4_timer_milliseconds << endl;
#endif

    // Ableton
    abletonHost = json["Ableton"]["Ableton Host"].asString();
    abletonSenderPort = json["Ableton"]["Ableton Sender Port"].asUInt();
    abletonReceiverPort = json["Ableton"]["Ableton Receiver Port"].asUInt();
    abletonFirstClipIndex = json["Ableton"]["First Clip Index"].asUInt();
    abletonArtistOffset = json["Ableton"]["Artist Offset"].asUInt();

    // TUIO
    tuioClientPort = json["TUIO"]["Client Port"].asUInt();

    return parsingSuccessful;
}
