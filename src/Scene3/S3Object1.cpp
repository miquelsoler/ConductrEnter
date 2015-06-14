//
//  S3Object1.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object1.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S3Object1::S3Object1(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3Object1::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}


#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3Object1::setup()
{
    S3BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);

    camera.setTarget(sphere);

    initialRotation = ofRandom(360);
    updateRotation();
}

///--------------------------------------------------------------
void S3Object1::update()
{
    S3BaseObj::update();

    if (isAnimated) updateRotation();
}

///--------------------------------------------------------------
void S3Object1::draw()
{
    S3BaseObj::draw();

    camera.begin(viewRectangle);

    ofSetLineWidth(1);
    ofSetColor(255);
    sphere.drawWireframe();
    ofSetColor(255);

    drawLoop();

    camera.end();
}

///--------------------------------------------------------------
void S3Object1::windowResized(ofResizeEventArgs &args)
{
    S3BaseObj::windowResized(args);

    sphere.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(sphere);
}

#pragma mark -

///--------------------------------------------------------------
void S3Object1::updateRotation()
{
    float spinX = sin(initialRotation + ofGetElapsedTimef()*.35f);
    float spinY = cos(initialRotation + ofGetElapsedTimef()*.075f);

    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0.0, 1.0, 0.0);
}

