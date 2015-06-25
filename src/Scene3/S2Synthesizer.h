//
//  S2Synthesizer.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/6/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2Synthesizer__
#define __ConductrEnter__S2Synthesizer__

#include <stdio.h>
#include "S2BaseObj.h"
#include "of3dGraphics.h"
#include "S2SynthesizerCircle.h"

class S2Synthesizer : public S2BaseObj
{
public:
    S2Synthesizer(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

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

    list<S2SynthesizerCircle *>  circles;
    float                       circlesMinRadius;
    float                       circlesMaxRadius;
    bool                        shouldAddCircle;

    ofParameter<float>          greyCircleRadius;
    float                       greyCircleAplha;

    float                       transitioningCircleRadius;
    float                       transitioningCircleAplha;
};

#endif /* defined(__ConductrEnter__S2Synthesizer__) */
