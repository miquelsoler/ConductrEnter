//
//  BaseObject.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 4/6/15.
//
//

#include "BaseObject.h"

///--------------------------------------------------------------
BaseObject::BaseObject(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath)
:   sceneNumObjects(numObjects),
    sceneObjectIndex(objectIndex),
    viewOriginX(_viewOriginX),
    viewWidth(_viewWidth)
{
    // Give width/4 left & right margin
    viewWidthMargin = viewWidth/4;
    viewWidth += (2 * viewWidthMargin);
    viewOriginX -= viewWidthMargin;
    viewHalfWidth = viewWidth / 2.0f;
    viewHalfHeight = ofGetHeight() / 2.0f;
    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, ofGetHeight());

    objPosition = ofPoint(0, 0, 0);

    ofAddListener(ofEvents().windowResized, this, &BaseObject::windowResized);
    
}
