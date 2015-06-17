//
//  S3NoiseSphere.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3NoiseSphere.h"

///--------------------------------------------------------------
S3NoiseSphere::S3NoiseSphere(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3NoiseSphere::loadSettings()
{
}

///--------------------------------------------------------------
void S3NoiseSphere::setup()
{
}

///--------------------------------------------------------------
void S3NoiseSphere::update()
{
}

///--------------------------------------------------------------
void S3NoiseSphere::draw()
{
}
