//
//  S4BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S4BaseObj.h"
#include "ofxAppUtils.h"

void S4BaseObj::initialize(float _viewOriginX, float _viewWidth)
{
    viewOriginX = _viewOriginX;
    viewWidth = _viewWidth;

    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, ofGetHeight());
}

void S4BaseObj::displaySettings()
{
    ofSetColor(127);
    ofxBitmapString(viewOriginX+5, 50)
    << "CAM DISTANCE: " << camera.getDistance();
    ofSetColor(200,200,200);
}
