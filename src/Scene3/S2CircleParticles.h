//
//  S2ExampleObject.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2CircleParticles__
#define __ConductrEnter__S2CircleParticles__

#include <stdio.h>
#include "S2BaseObj.h"
#include "of3dGraphics.h"
#include "ofxTweenzor.h"

#include "demoParticle.h"


class S2CircleParticles : public S2BaseObj
{
public:
    S2CircleParticles(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void loadSettings();
    virtual void setPositionFromScreenCoords(int screenX, int screenY);
    
    // ELOI
    ofMesh                  circleMesh;
    void                    recalculateCircle();
    ofParameter<float>      circleRadius;
    ofParameter<int>        numDotsInCircle;
    ofParameter<bool>       updateCircle;
    float                   scaleCircle;
    
    // PARTICLES
    void                    resetParticles();
    particleMode            currentMode;
    vector<demoParticle>    p;
    vector <ofPoint>        attractPoints;
    vector <ofPoint>        attractPointsWithMovement;
    ofParameter<bool>       updateParticles;
    ofParameter<float>      baseAge;
    int                     particlesState;
    void                    changeParticleState(int s);
    float                   volumeParticleScale;
    void                    changeParticleSize(int i);
    
    
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

    float kk;

    ofSpherePrimitive   sphere;
    float               sphereScale;
    ofColor             sphereColor;
    
    float                   transitioningCircleRadius;
    float                   transitioningCircleAlpha;
    float                   transitioningSphereScale;

    
};

#endif /* defined(__ConductrEnter__S2CircleParticles___) */
