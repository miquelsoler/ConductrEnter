//
//  SettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 25/5/15.
//
//

#include "SettingsManager.h"

#include "ofLog.h"

const std::string filename = "settings.json";

bool SettingsManager::loadSettings()
{
    cout << "PARSING JSON SETTINGS:" << endl;
    bool parsingSuccessful = json.open(filename);
    cout << "Result: " << parsingSuccessful << endl;

    // Screen
    window_width = json["Screen"]["Window Width"].asUInt();
    window_height = json["Screen"]["Window Height"].asUInt();
    cout << "[Screen] width=" << window_width << " height=" << window_height << endl;

    // Scene management
    fade_in_milliseconds = json["Scenes"]["FadeIn Milliseconds"].asUInt();
    fade_out_milliseconds = json["Scenes"]["FadeOut Milliseconds"].asUInt();
    scene4_timer_milliseconds = json["Scenes"]["Scene4 Timer Milliseconds"].asUInt();
    cout << "[Scenes] fadeIn=" << fade_in_milliseconds << " fadeOut=" << fade_out_milliseconds << " scene4Timer=" << scene4_timer_milliseconds << endl;

    return parsingSuccessful;
}
