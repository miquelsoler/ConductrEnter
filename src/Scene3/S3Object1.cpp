//
//  S3Object1.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object1.h"

S3Object1::S3Object1(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object1::setup()
{
    sphere.setRadius(viewWidth * .12);
    objPosition.x = viewOriginX + viewHalfWidth;
    objPosition.y = viewHalfHeight;
    sphere.setPosition(objPosition);

    camera.setTarget(sphere);
    camera.setPosition(objPosition);
    camera.setDistance(camDistance);

    initialRotation = ofRandom(360);
    updateRotation();

    gui.setPosition(viewOriginX, 0);
}

void S3Object1::update()
{
#ifdef OF_DEBUG
    // Update object parameters from XML
    camera.setDistance(camDistance);
#endif

    if (isAnimated) updateRotation();
}

void S3Object1::draw()
{
    camera.begin(viewRectangle);

    ofSetLineWidth(1);
    ofSetColor(255);
    sphere.drawWireframe();
    ofSetColor(255);

    drawLoop();

    camera.end();

#ifdef OF_DEBUG
    gui.draw();
#endif
}

/**/ // OSC
void S3Object1::setY(float newY)
{
    float spherePosX = viewOriginX + viewHalfWidth;
    objPosition.set(spherePosX, newY);
    sphere.setPosition(objPosition);
}

void S3Object1::loadSettings()
{
    if (settingsPath.empty()) return;

    gui.setup("Settings", settingsPath);
    gui.add(camDistance.set("Camera_Distance", 0, 0, 300));
    gui.add(loopRadius.set("Loop_Radius", 0, 0, 100));
    gui.add(loopAngle.set("Loop_Angle", 0, 0, 720));

    gui.loadFromFile(settingsPath);
}

void S3Object1::updateRotation()
{
    float spinX = sin(initialRotation + ofGetElapsedTimef()*.35f);
    float spinY = cos(initialRotation + ofGetElapsedTimef()*.075f);

    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0.0, 1.0, 0.0);
}

void S3Object1::windowResized(ofResizeEventArgs &args)
{
//    viewWidh, viewHalfWidth, viewHalfHeight, objPosition, camera position, camera distance, viewRectangle
    viewWidth = args.width / sceneNumObjects;
    viewHalfWidth = viewWidth / 2.0f;
    viewHalfHeight = args.height / 2.0f;
    viewOriginX = sceneObjectIndex * viewWidth;
    objPosition.x = viewOriginX + viewHalfWidth;
    objPosition.y = viewHalfHeight;
    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, args.height);

    sphere.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(sphere);
    camera.setDistance(camDistance);

    gui.setPosition(viewOriginX, 0);
}
