//
//  S3ExampleObject.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S3ExampleObject.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S3ExampleObject::S3ExampleObject(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3ExampleObject::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}


#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3ExampleObject::setup()
{
    S3BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);

    camera.setTarget(sphere);

    initialRotation = ofRandom(360);
    updateRotation();

    isFirstSetup = false;
}

///--------------------------------------------------------------
void S3ExampleObject::updateInactive()
{
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S3ExampleObject::updateTransitioning()
{
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S3ExampleObject::updateActive()
{
}

///--------------------------------------------------------------
void S3ExampleObject::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3ExampleObject::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3ExampleObject::drawActive()
{
    camera.begin(viewRectangle);
    {
        ofSetLineWidth(1);
        ofSetColor(255);
        sphere.drawWireframe();
        ofSetColor(255);

        drawWhiteCircle();
        if (pinchEnabled) drawPinchCircle();
        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S3ExampleObject::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}

#pragma mark -

///--------------------------------------------------------------
void S3ExampleObject::updateRotation()
{
    float spinX = sin(initialRotation + ofGetElapsedTimef()*.35f);
    float spinY = cos(initialRotation + ofGetElapsedTimef()*.075f);

    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0.0, 1.0, 0.0);
}
