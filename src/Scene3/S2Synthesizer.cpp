//
//  S2Synthesizer.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/6/15.
//
//

#include "S2Synthesizer.h"

#include "ofxTweenzor.h"


const float VOLUME_THRESHOLD = 0.6f; // TODO Must be normalized in Ableton.

#pragma mark - Initialization

///--------------------------------------------------------------
S2Synthesizer::S2Synthesizer(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2Synthesizer::loadSettings()
{
    if (settingsPath.empty()) return;
    S2BaseObj::initSharedSettings();

    // Custom object settings go here
    gui.add(greyCircleRadius.set("Grey Circle Radius", 8.0f, 1.0f, 30.0f));

    gui.loadFromFile(settingsPath);
}


#pragma mark - Basic object methods

///--------------------------------------------------------------
void S2Synthesizer::setup()
{
    S2BaseObj::setup();

    circlesMaxRadius = radius/4.0f;
    circlesMinRadius = circlesMaxRadius - 5.0f;

    circles.clear();
    shouldAddCircle = true;

    isFirstSetup = false;

    Tweenzor::resetAllTweens();
}

///--------------------------------------------------------------
void S2Synthesizer::initInactive()
{
    float alphaFrom = 25.0f;
    float alphaTo = 50.0f;
    float delay = 0.0f;
    float duration = 1.0f;

    Tweenzor::add(&greyCircleAplha, alphaFrom, alphaTo, delay, duration, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&greyCircleAplha);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S2Synthesizer::onCompleteInactive);
}

void S2Synthesizer::onCompleteInactive(float* arg)
{
    if (!shouldChangeState)
        initInactive();
    else
        changeState();
}

void S2Synthesizer::updateInactive()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
}

void S2Synthesizer::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2Synthesizer::initTransitioning()
{
    float radiusFrom = greyCircleRadius;
    float radiusTo = radius;
    float alphaFrom = 150.0f;
    float alphaTo = 0.0f;
    float duration = 0.2f;
    float delay = 0.0f;

    Tweenzor::add(&transitioningCircleRadius, radiusFrom, radiusTo, delay, duration, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&transitioningCircleRadius);
    Tweenzor::addCompleteListener(tween, this, &S2Synthesizer::onCompleteTransitioning);

    Tweenzor::add(&transitioningCircleAplha, alphaFrom, alphaTo, delay, duration, EASE_IN_OUT_SINE);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
}

void S2Synthesizer::onCompleteTransitioning(float* arg)
{
    changeState();
}

void S2Synthesizer::updateTransitioning()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
}

void S2Synthesizer::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2Synthesizer::initActive()
{
}

void S2Synthesizer::updateActive()
{
    list<S2SynthesizerCircle *>::iterator it;
    for (it=circles.begin(); it!=circles.end();)
    {
        if ((*it)->isDone())
        {
            circles.erase(it++);
        }
        else
        {
            (*it)->update(objPosition);
            ++it;
        }
    }
}

void S2Synthesizer::drawActive()
{
    camera.begin(viewRectangle);
    {
        // Grey circle
        ofFill();
        ofDisableLighting();
        ofSetColor(255, 255, 255, int(greyCircleAplha));
        ofCircle(objPosition.x, objPosition.y, 0, greyCircleRadius);

        // Transitioning circle
        if (currentState == S3ObjStateTransitioning)
        {
            ofFill();
            ofDisableLighting();
            ofSetColor(255, 255, 255, int(transitioningCircleAplha));
            ofCircle(objPosition.x, objPosition.y, 0, transitioningCircleRadius);
        }

        for (list<S2SynthesizerCircle *>::iterator it = circles.begin(); it!=circles.end(); ++it)
            (*it)->draw();

        drawPinchCircle();
        drawPinchColor();
        drawWhiteCircle();
        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S2Synthesizer::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);
}

///--------------------------------------------------------------
void S2Synthesizer::volumeChanged(float &newVolume)
{
    if (newVolume >= VOLUME_THRESHOLD)
    {
        if (shouldAddCircle)
        {
            addCircle();
            shouldAddCircle = false;
        }
    }
    else
    {
        shouldAddCircle = true;
    }
}

///--------------------------------------------------------------
void S2Synthesizer::addCircle()
{
    float circleRadius = ofRandom(circlesMinRadius, circlesMaxRadius);
    float maxValidRadius = radius - circlesMaxRadius;

    float angle = ofDegToRad(ofRandom(0.0f, 360.0f));
    float displacement= sqrt(ofRandom(0.3f, 1.0f)) * maxValidRadius;
    float x = displacement * cos(angle);
    float y = displacement * sin(angle);

    ofPoint offset = ofPoint(x, y, 0);

    S2SynthesizerCircle *circle = new S2SynthesizerCircle(objPosition, offset, circleRadius);
    circles.push_back(circle);
}
