//
//  S3Object3.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object3.h"

S3Object3::S3Object3(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object3::setup()
{
}

void S3Object3::update()
{
}

void S3Object3::draw()
{
}

void S3Object3::loadSettings()
{
}
