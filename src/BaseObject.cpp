//
//  BaseObject.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 4/6/15.
//
//

#include "BaseObject.h"

BaseObject::BaseObject(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath)
:   sceneNumObjects(numObjects),
    sceneObjectIndex(objectIndex),
    viewOriginX(_viewOriginX),
    viewWidth(_viewWidth)
{
    viewHalfWidth = viewWidth / 2.0f;
    viewHalfHeight = ofGetHeight() / 2.0f;
    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, ofGetHeight());

    objPosition = ofPoint(viewOriginX + viewHalfWidth, viewHalfHeight);

    ofAddListener(ofEvents().windowResized, this, &BaseObject::windowResized);
}

float BaseObject::getViewOriginX()
{
    return viewOriginX;
}