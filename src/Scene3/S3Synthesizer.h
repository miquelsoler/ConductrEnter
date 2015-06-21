//
//  S3Synthesizer.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/6/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Synthesizer__
#define __ConductrEnter__S3Synthesizer__

#include <stdio.h>
#include "S3BaseObj.h"
#include "of3dGraphics.h"

class S3SynthCircle
{
public:
    ofPoint position;
    float radius;
    float alpha;
};


class S3Synthesizer : public S3BaseObj
{
public:
    S3Synthesizer(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void loadSettings();
    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void initInactive();
    void onCompleteInactive(float* arg);
    virtual void updateInactive();
    virtual void drawInactive();

    virtual void initTransitioning();
    void onCompleteTransitioning(float* arg);
    virtual void updateTransitioning();
    virtual void drawTransitioning();

    virtual void initActive();
    virtual void updateActive();
    virtual void drawActive();

    virtual void volumeChanged(float &newVolume);

    void addCircle();

    list<S3SynthCircle>     circles;
    float                   circlesMinRadius;
    float                   circlesMaxRadius;
};

#endif /* defined(__ConductrEnter__S3Synthesizer__) */
