//
//  S4Object1.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S4Object1.h"

void S4Object1::setup()
{
    float spherePosX = viewOriginX + viewWidth/2.0f;
    float spherePosY = ofGetHeight() / 2.0f;
    sphere.setRadius(viewWidth * .12);
    sphere.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(sphere);
    camera.setDistance(camDistance);

    initialRotation = ofRandom(60);
}

void S4Object1::update()
{
#ifdef OF_DEBUG
    // Update object parameters from XML
    camera.setDistance(camDistance);
#endif

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

    drawLoop();

    camera.end();

#ifdef OF_DEBUG
    gui.draw();
#endif
}

void S4Object1::loadSettings()
{
    gui.setup("Settings");
    gui.add(camDistance.set("Camera_Distance", 0, 0, 300));
    gui.add(loopRadius.set("Loop_Radius", 0, 0, 100));

    gui.loadFromFile(settingsPath);
}
