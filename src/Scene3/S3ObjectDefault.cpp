//
//  S3ObjectDefault.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S3ObjectDefault.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S3ObjectDefault::S3ObjectDefault(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3ObjectDefault::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}


#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3ObjectDefault::setup()
{
    S3BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);

    camera.setTarget(sphere);

    initialRotation = ofRandom(360);
    updateRotation();
}

///--------------------------------------------------------------
void S3ObjectDefault::updateInactive()
{
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S3ObjectDefault::updateTransitioning()
{
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S3ObjectDefault::updateActive()
{
}

///--------------------------------------------------------------
void S3ObjectDefault::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3ObjectDefault::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3ObjectDefault::drawActive()
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
void S3ObjectDefault::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}

#pragma mark -

///--------------------------------------------------------------
void S3ObjectDefault::updateRotation()
{
    float spinX = sin(initialRotation + ofGetElapsedTimef()*.35f);
    float spinY = cos(initialRotation + ofGetElapsedTimef()*.075f);

    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0.0, 1.0, 0.0);
}
