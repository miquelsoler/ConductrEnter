//
//  S3DrumsAmoeba.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3DrumsAmoeba__
#define __ConductrEnter__S3DrumsAmoeba__

#include <stdio.h>
#include "S3BaseObj.h"

class S3DrumsAmoeba : public S3BaseObj
{
public:
    S3DrumsAmoeba(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void volumeChanged(float &newVolume);

    ofIcoSpherePrimitive    sphere;

    float                   radiusTween;
    float                   radiusMax;
    float                   radiusMin;

    ofImage noiseImage;
    ofPixels                noisePixels;
    ofShader                shader;

    ofParameter<float>      divider;
    ofParameter<float>      tempo;
    // NOISE GUI
    ofParameter<float>      noiseFrequency;
    ofParameter<bool>       animate;
    ofParameter<bool>       doThreshold;
    ofParameter<int>        thresholdLow;
    ofParameter<int>        thresholdHigh;
    ofParameter<bool>       invert;
    ofParameter<bool>       showNormals;
    ofParameter<float>  offset;

    // Candidats a moure a l'objecte base
    ofImage imgColorsCircle;
    ofLight     pointLight1;
    ofLight     pointLight2;
    ofLight     pointLight3;
};

#endif /* defined(__ConductrEnter__S3DrumsAmoeba__) */
