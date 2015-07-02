//
//  S2DrumsAmoeba.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2NoisePlexus__
#define __ConductrEnter__S2NoisePlexus__

#include <stdio.h>
#include "S2BaseObj.h"
#include "ofxSimpleTimer.h"
#include "Tweenzor.h"


class S2NoisePlexus : public S2BaseObj
{
public:
    S2NoisePlexus(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);
    
    virtual void setup();
    virtual void loadSettings();
    
    virtual void setPositionFromScreenCoords(int screenX, int screenY);
    
private:
    
    virtual void initInactive();
    virtual void updateInactive();
    virtual void drawInactive();
    
    virtual void initTransitioning();
    virtual void updateTransitioning();
    virtual void drawTransitioning();
    void onCompleteTransitioning(float* arg);
    void onCompleteTransitioningToActive(float* arg);
    
    virtual void initActive() {};
    virtual void updateActive();
    virtual void drawActive();
    
    virtual void volumeChanged(float &newVolume);
    
    ofIcoSpherePrimitive    sphere;
    
    ofImage                 noiseImage;
    ofPixels                noisePixels;
    ofShader                shader;
    
    ofParameter<float>      tempo;
    // NOISE GUI
    ofParameter<float>      noiseFrequency;
    ofParameter<bool>       animate;
    ofParameter<bool>       doThreshold;
    ofParameter<int>        thresholdLow;
    ofParameter<int>        thresholdHigh;
    ofParameter<bool>       invert;
    ofParameter<bool>       showNormals;
    ofParameter<float>      offset;
    
    ofParameter<float> plexusMinDistance;
    ofParameter<float> plexusMaxDistance;
    ofParameter<float> noiseMinDistance;
    ofParameter<float> noiseMaxDistance;
    
    ofParameter<int> mode;
    float               vertexOffset;
    float               vertexNoise;
    ofMesh              plexus;
    bool                nothingToDraw;

    ofLight pointLight1;
    ofLight pointLight2;
    ofLight pointLight3;

    
    
    float                   stableOffset;
    
    float                   inactiveNoiseFrequency;
    float                   inactiveCircleRadius;
    float                   inactiveCircleAlpha;
    
    float                   transitionCircleRadius;
    float                   transitionCircleAlpha;
    
    float                   volumeCircleRadius;
    float                   volumeCircleAlpha;
    float                   activeNoiseFrequency;
    
    float                   maxVolumeCircleRadius;
    float                   maxVolumeCircleAlpha;
    float                   maxOffset;
    
};

#endif /* defined(__ConductrEnter__S2DrumsAmoeba__) */
