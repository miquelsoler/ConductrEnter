//
//  BaseObject.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 4/6/15.
//
//

#pragma once

#ifndef __ConductrEnter__BaseObject__
#define __ConductrEnter__BaseObject__

#include <stdio.h>
#include "ofEasyCam.h"
#include "ofMain.h"

#include "BaseScene.h"

class BaseObject
{
public:

    BaseObject(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath = "");
    virtual ~BaseObject() {}

    virtual void setY(float newY) = 0;
    float getViewOriginX();

protected:
    // Parent related attributes
    unsigned int sceneNumObjects;
    unsigned int sceneObjectIndex;

    // Position
    ofPoint objPosition;

    // Viewport
    float viewOriginX, viewWidth, viewHalfWidth, viewHalfHeight;
    ofRectangle viewRectangle;

    // Listener method to detect window changes
    virtual void windowResized(ofResizeEventArgs &args) {}
};

#endif /* defined(__ConductrEnter__BaseObject__) */
