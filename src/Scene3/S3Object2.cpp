//
//  S3Object2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object2.h"

S3Object2::S3Object2(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object2::setup()
{
}

void S3Object2::update()
{
}

void S3Object2::draw()
{
}

void S3Object2::loadSettings()
{
}
