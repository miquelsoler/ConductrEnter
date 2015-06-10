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
    fade_in_milliseconds = json["Scenes"]["FadeIn Milliseconds"].asUInt();
    fade_out_milliseconds = json["Scenes"]["FadeOut Milliseconds"].asUInt();
    scene4_timer_milliseconds = json["Scenes"]["Scene4 Timer Milliseconds"].asUInt();
#ifdef OF_DEBUG
    cout << "[Scenes] fadeIn=" << fade_in_milliseconds << " fadeOut=" << fade_out_milliseconds << " scene4Timer=" << scene4_timer_milliseconds << endl;
#endif
    // OSC
    oscAbletonHost = json["OSC"]["Ableton Host"].asString();
    oscAbletonSenderPort = json["OSC"]["Ableton Sender Port"].asUInt();
    oscAbletonReceiverPort = json["OSC"]["Ableton Receiver Port"].asUInt();

    return parsingSuccessful;
}
