//
//  S2ExampleObject.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S2ExampleObject.h"

#include "ofxTweenzor.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S2ExampleObject::S2ExampleObject(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2ExampleObject::loadSettings()
{
    if (settingsPath.empty()) return;
    S2BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}


#pragma mark - Basic object methods

///--------------------------------------------------------------
void S2ExampleObject::setup()
{
    S2BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(4);

    camera.setTarget(sphere);

    isFirstSetup = false;

    Tweenzor::resetAllTweens();
}

///--------------------------------------------------------------
void S2ExampleObject::initInactive()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.9f, 0.0f, 1.0f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S2ExampleObject::onCompleteInactive);

    sphereScale = 1;
}

void S2ExampleObject::onCompleteInactive(float* arg)
{
    if (!shouldChangeState)
        initInactive();
    else
        changeState();
}

void S2ExampleObject::updateInactive()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
//    updateActive(); // Delete this line if it needs a custom update
}

void S2ExampleObject::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------
void S2ExampleObject::initTransitioning()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.0f, 0.0f, 0.5f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S2ExampleObject::onCompleteTransitioning);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
}

void S2ExampleObject::onCompleteTransitioning(float* arg)
{
    changeState();
}

void S2ExampleObject::updateTransitioning()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
//    updateActive(); // Delete this line if it needs a custom update
}

void S2ExampleObject::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2ExampleObject::initActive()
{
}

void S2ExampleObject::updateActive()
{
}

void S2ExampleObject::drawActive()
{
    camera.begin();
    {
        ofSetLineWidth(1);
        switch(currentState)
        {
            case S3ObjStateInactive:        sphereColor = ofColor::red; break;
            case S3ObjStateTransitioning:   sphereColor = ofColor::orange; break;
            case S3ObjStateActive:          sphereColor = ofColor::green; break;
            default:                        break;
        }
        ofSetColor(sphereColor);
        sphere.setScale(sphereScale);
        float spinX = sin(ofGetElapsedTimef()*.35f);
        float spinY = cos(ofGetElapsedTimef()*.075f);

        sphere.rotate(spinX, 1.0, 0.0, 0.0);
        sphere.rotate(spinY, 0.0, 1.0, 0.0);

        sphere.drawWireframe();
        ofSetColor(255);

        drawWhiteCircle();
        if (pinchEnabled)
        {
            drawPinchCircle();
            drawPinchColor();
        }
        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S2ExampleObject::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}

///--------------------------------------------------------------
void S2ExampleObject::volumeChanged(float &newVolume)
{
    sphereColor = ofColor(ofMap(newVolume, 0.0f, 1.0f, 40.0f, 255.0f));
}
