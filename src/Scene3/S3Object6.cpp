//
//  S3Object6.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object6.h"

S3Object6::S3Object6(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object6::setup()
{
}

void S3Object6::update()
{
}

void S3Object6::draw()
{
}

void S3Object6::loadSettings()
{
}
