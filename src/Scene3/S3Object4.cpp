//
//  S3Object4.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object4.h"

S3Object4::S3Object4(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object4::setup()
{
}

void S3Object4::update()
{
}

void S3Object4::draw()
{
}

void S3Object4::loadSettings()
{
}
