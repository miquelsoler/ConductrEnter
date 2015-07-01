//
//  S2NoiseSphere.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2NoiseSphere__
#define __ConductrEnter__S2NoiseSphere__

#include <stdio.h>
#include "S2BaseObj.h"
#include "ofxTweenzor.h"


class S2NoiseSphere : public S2BaseObj
{
public:
    S2NoiseSphere(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void initInactive();
    virtual void updateInactive();
    virtual void drawInactive();

    virtual void initTransitioning() ;
    virtual void updateTransitioning();
    virtual void drawTransitioning();
    void onCompleteTransitioning(float* arg);
    void onCompleteToActive(float* arg);

    virtual void initActive();
    virtual void updateActive();
    virtual void drawActive();

    virtual void volumeChanged(float &newVolume);

    ofSpherePrimitive       sphere;
    ofSpherePrimitive       sphereAudio;
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
    
    // Transitioning state
    float                   stableNoiseFrequency;
    float                   stableOffset;
    float                   activeOffset;
    float                   activeNoiseFrequency;
    
    float                   inactiveCircleRadius;
    float                   inactiveCircleAlpha;
    float                   transitionCircleRadius;
    float                   transitionCircleAlpha;
    float                   activeCircleRadius;
    float                   activeCircleAlpha;

    float                   maxCircleRadius;
    float                   maxCircleAlpha;

};

#endif /* defined(__ConductrEnter__S2NoiseSphere__) */
