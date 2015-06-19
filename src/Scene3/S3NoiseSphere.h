//
//  S3NoiseSphere.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3NoiseSphere__
#define __ConductrEnter__S3NoiseSphere__

#include <stdio.h>
#include "S3BaseObj.h"

class S3NoiseSphere : public S3BaseObj
{
public:
    S3NoiseSphere(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void updateInactive();
    virtual void updateTransitioning();
    virtual void updateActive();
    virtual void drawInactive();
    virtual void drawTransitioning();
    virtual void drawActive();

    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void volumeChanged(float &newVolume) {};

    ofImage             imgColorsCircle;
    ofSpherePrimitive   sphere;
    vector<ofMeshFace>      sphereFacesOriginal;
    vector<ofMeshFace>      sphereFacesCurrent;
    vector<ofVec3f>         vertexNormals;
    vector<ofVec3f>         vertexOriginals; // Sponsored by Werther's Originals (https://en.wikipedia.org/wiki/Werther%27s_Original)
    float                   vertexOffset;

    // NOISE GUI
    ofParameter<float>      tempo;
    ofParameter<float>      noiseFrequency;
    ofParameter<bool>       doThreshold;
    ofParameter<int>        thresholdLow;
    ofParameter<int>        thresholdHigh;
    ofParameter<float>      offset;
    ofParameter<int>        mode;

    int                     noiseStartX, noiseStartY;


};

#endif /* defined(__ConductrEnter__S3NoiseSphere__) */
