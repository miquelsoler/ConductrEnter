//
//  S3Drums.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
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
    virtual void update();
    virtual void draw();

    virtual void loadSettings();

    virtual void setY(float newY);

private:

    ofIcoSpherePrimitive sphere1, sphere2;
    vector<ofMeshFace> trianglesOriginal1, trianglesCurrent1;
    vector<ofMeshFace> trianglesOriginal2, trianglesCurrent2;
    vector<float> noises1, noises2;

    ofxSimpleTimer beatTimer;
    float vertexDistance;

    void setupTween();
    void timerCompleteHandler(int &args);
    void tweenCompleteHandler(float* arg);

    ofParameter<float> tweenBegin, tweenEnd, tweenDuration;

    virtual void windowResized(ofResizeEventArgs &args);
};

#endif /* defined(__ConductrEnter__S4Object2__) */
