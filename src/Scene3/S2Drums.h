//
//  S2Drums.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S2Drums__
#define __ConductrEnter__S3Drums__

#include <stdio.h>
#include "S2BaseObj.h"
#include "ofxSimpleTimer.h"
#include "Tweenzor.h"

class S2Drums : public S2BaseObj
{
public:

    S2Drums(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

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
    virtual void windowResized(ofResizeEventArgs &args);

    void sphereResolutionChanged(int &newSphereResolution);

    ofSpherePrimitive       sphere;
    vector<ofMeshFace>      trianglesOriginal, trianglesCurrent;
    vector<float>           noises;
    float                   vertexDistance;

    float                   sphereGrayColor;

    ofParameter<int>        sphereResolution;
    ofParameter<float>      spherePointSize;
    ofParameter<float>      sphereVolumeScale;

    // Transitioning state
    float                   transitioningCircleRadius;
    float                   transitioningCircleAlpha;
    ofSpherePrimitive       transitioningSphere;
    float                   transitioningSphereScale;
    float                   transitioningSphereAlpha;
};

#endif /* defined(__ConductrEnter__S2Drums__) */
