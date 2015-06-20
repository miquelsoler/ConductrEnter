//
//  S3Drums.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S3Drums__
#define __ConductrEnter__S3Drums__

#include <stdio.h>
#include "S3BaseObj.h"
#include "ofxSimpleTimer.h"
#include "Tweenzor.h"

class S3Drums : public S3BaseObj
{
public:

    S3Drums(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath);

    virtual void setup();
    virtual void loadSettings();

    virtual void setPositionFromScreenCoords(int screenX, int screenY);

private:

    virtual void initInactive() {};
    virtual void updateInactive();
    virtual void drawInactive();

    virtual void initTransitioning() {};
    virtual void updateTransitioning();
    virtual void drawTransitioning();

    virtual void initActive() {};
    virtual void updateActive();
    virtual void drawActive();

    virtual void volumeChanged(float &newVolume);
    virtual void windowResized(ofResizeEventArgs &args);

    ofIcoSpherePrimitive    sphere1, sphere2;
    vector<ofMeshFace>      trianglesOriginal1, trianglesCurrent1;
    vector<ofMeshFace>      trianglesOriginal2, trianglesCurrent2;
    vector<float>           noises1, noises2;
    float                   vertexDistance;
};

#endif /* defined(__ConductrEnter__S4Object2__) */
