//
//  S4Object2.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__S4Object2__
#define __ConductrEnter__S4Object2__

#include <stdio.h>
#include "S4BaseObj.h"


class S4Object2 : public S4BaseObj
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();

private:
    void computeMesh();
    void drawTendrils(ofCamera* _camera);

    ofVboMesh				grassMesh;
    ofShader				grassShader;

    ofParameter<int>		placementResolution;
    ofParameter<float>		placementSize;
    ofParameter<float>		placementNoiseSpaceFrequency;
    ofParameter<float>		placementBottomThreshold;

    ofParameter<float>		stalkRadius;
    ofParameter<float>		stalkHeight;
    ofParameter<float>		swayingMaxAngle;
    ofParameter<float>		swayingTimeScale;
    ofParameter<float>		swayingNoiseSpaceFrequency;
    ofParameter<float>		swayingTimeMaxDifference;
};

#endif /* defined(__ConductrEnter__S4Object2__) */
