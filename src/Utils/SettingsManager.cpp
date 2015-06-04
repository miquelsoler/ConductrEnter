//
//  SettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 25/5/15.
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
    cout << "PARSING RESULT: " << parsingSuccessful << endl;

    // Screen
    window_width = json["Screen"]["Window Width"].asUInt();
    window_height = json["Screen"]["Window Height"].asUInt();
    cout << "[Screen] width=" << window_width << " height=" << window_height << endl;

    // Scene management
    fade_in_milliseconds = json["Scenes"]["FadeIn Milliseconds"].asUInt();
    fade_out_milliseconds = json["Scenes"]["FadeOut Milliseconds"].asUInt();
    scene4_timer_milliseconds = json["Scenes"]["Scene4 Timer Milliseconds"].asUInt();
    cout << "[Scenes] fadeIn=" << fade_in_milliseconds << " fadeOut=" << fade_out_milliseconds << " scene4Timer=" << scene4_timer_milliseconds << endl;

    // OSC
    oscAbletonHost = json["OSC"]["Ableton Host"].asString();
    oscAbletonPort = json["OSC"]["Ableton Port"].asUInt();

    return parsingSuccessful;
}
