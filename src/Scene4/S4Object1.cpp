//
//  S4Object1.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S4Object1.h"

void S4Object1::setup()
{
    float spherePosX = viewOriginX + viewWidth/2.0f;
    float spherePosY = ofGetHeight() / 2.0f;
    sphere.setRadius(viewWidth * .12);
    sphere.setPosition(spherePosX, spherePosY, 0);

    camera.setPosition(spherePosX, spherePosY, 0);
    camera.setTarget(sphere);
    camera.setDistance(220);

    initialRotation = ofRandom(60);
}

void S4Object1::update()
{
    float spinX = sin(initialRotation + ofGetElapsedTimef()*.35f);
    float spinY = cos(initialRotation + ofGetElapsedTimef()*.075f);

    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0.0, 1.0, 0.0);
}

void S4Object1::draw()
{
    camera.begin(viewRectangle);

    ofSetColor(127,255,127);
    sphere.drawWireframe();
    ofSetColor(255);

    camera.end();

#ifdef OF_DEBUG
    displaySettings();
#endif
}
