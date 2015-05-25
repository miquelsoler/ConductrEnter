//
//  SettingsManager.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 25/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__SettingsManager__
#define __ConductrEnter__SettingsManager__

#include <stdio.h>
#include "ofxJSON.h"

class SettingsManager
{
public:
    static SettingsManager &getInstance()
    {
        static SettingsManager instance;
        return instance;
    }

    bool loadSettings();

    // Screen
    unsigned int window_width;
    unsigned int window_height;

    // Scene management
    unsigned int fade_in_milliseconds;
    unsigned int fade_out_milliseconds;
    unsigned long scene4_timer_milliseconds;

private:
    ofxJSONElement json;
};

/*
 class Stopwords {
 public:
 static Stopwords &getInstance() {
 static Stopwords instance;
 return instance;
 }

 ~Stopwords();
 std::map<std::string,short> getMap();

 private:
 Stopwords();
 std::map<std::string,short> diccionario;
 }; */
#endif /* defined(__ConductrEnter__SettingsManager__) */
