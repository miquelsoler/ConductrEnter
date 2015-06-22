//
//  S3ExampleObject.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S3ExampleObject.h"

#include "ofxTweenzor.h"

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
    sphere.setResolution(4);

    camera.setTarget(sphere);

    isFirstSetup = false;

    Tweenzor::resetAllTweens();
}

///--------------------------------------------------------------
void S3ExampleObject::initInactive()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.9f, 0.0f, 1.0f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3ExampleObject::onCompleteInactive);

    sphereScale = 1;
}

void S3ExampleObject::onCompleteInactive(float* arg)
{
    if (!shouldChangeState)
        initInactive();
    else
        changeState();
}

void S3ExampleObject::updateInactive()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
//    updateActive(); // Delete this line if it needs a custom update
}

void S3ExampleObject::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------
void S3ExampleObject::initTransitioning()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.0f, 0.0f, 0.5f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3ExampleObject::onCompleteTransitioning);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
}

void S3ExampleObject::onCompleteTransitioning(float* arg)
{
    changeState();
}

void S3ExampleObject::updateTransitioning()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
//    updateActive(); // Delete this line if it needs a custom update
}

void S3ExampleObject::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3ExampleObject::initActive()
{
}

void S3ExampleObject::updateActive()
{
}

void S3ExampleObject::drawActive()
{
    camera.begin(viewRectangle);
    {
        ofSetLineWidth(1);
        switch(currentState)
        {
            case S3ObjStateInactive:        sphereColor = ofColor::red; break;
            case S3ObjStateTransitioning:   sphereColor = ofColor::orange; break;
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

///--------------------------------------------------------------
void S3ExampleObject::volumeChanged(float &newVolume)
{
    sphereColor = ofColor(ofMap(newVolume, 0.0f, 1.0f, 40.0f, 255.0f));
}
