//
//  S3Synthesizer.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/6/15.
//
//

#include "S3Synthesizer.h"

#include "ofxTweenzor.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S3Synthesizer::S3Synthesizer(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3Synthesizer::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}


#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3Synthesizer::setup()
{
    S3BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(4);

    camera.setTarget(sphere);

//    updateRotation();

    isFirstSetup = false;

    Tweenzor::resetAllTweens();
}

///--------------------------------------------------------------
void S3Synthesizer::initInactive()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.9f, 0.0f, 1.0f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3Synthesizer::onCompleteInactive);

    sphereScale = 1;
}

void S3Synthesizer::onCompleteInactive(float* arg)
{
    if (!shouldChangeState)
        initInactive();
    else
        changeState();
}

void S3Synthesizer::updateInactive()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
//    updateActive(); // Delete this line if it needs a custom update
}

void S3Synthesizer::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------
void S3Synthesizer::initTransitioning()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.0f, 0.0f, 0.5f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3Synthesizer::onCompleteTransitioning);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
}

void S3Synthesizer::onCompleteTransitioning(float* arg)
{
    changeState();
}

void S3Synthesizer::updateTransitioning()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
//    updateActive(); // Delete this line if it needs a custom update
}

void S3Synthesizer::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3Synthesizer::initActive()
{
}

void S3Synthesizer::updateActive()
{
}

void S3Synthesizer::drawActive()
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
void S3Synthesizer::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}

///--------------------------------------------------------------
void S3Synthesizer::volumeChanged(float &newVolume)
{
    sphereColor = ofColor(ofMap(newVolume, 0.0f, 1.0f, 40.0f, 255.0f));
}
