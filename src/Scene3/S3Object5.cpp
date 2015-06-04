//
//  S3Object5.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object5.h"

S3Object5::S3Object5(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object5::setup()
{
}

void S3Object5::update()
{
}

void S3Object5::draw()
{
}

void S3Object5::loadSettings()
{
}
