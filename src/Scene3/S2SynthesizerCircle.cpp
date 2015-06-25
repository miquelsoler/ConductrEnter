//
// Created by Miquel Àngel Soler on 22/6/15.
//

#include "S2SynthesizerCircle.h"
#include "ofxTweenzor.h"

S2SynthesizerCircle::S2SynthesizerCircle(ofPoint objectCenter, ofPoint _offsetPosition, float _radius)
{
    offsetPosition = _offsetPosition;
    position = ofPoint(objectCenter.x + offsetPosition.x, objectCenter.y + offsetPosition.y, objectCenter.z);
    radius = _radius;
    alpha = 255.0f;

    done = false;

    Tweenzor::add(&alpha, 255.0f, 0.0f, 0.0f, 1.0f, EASE_LINEAR);
    Tween *tween = Tweenzor::getTween(&alpha);
    Tweenzor::addCompleteListener(tween, this, &S2SynthesizerCircle::onCompleteTween);
}

S2SynthesizerCircle::~S2SynthesizerCircle()
{
}

void S2SynthesizerCircle::update(ofPoint objectCenter)
{
    position = ofPoint(objectCenter.x + offsetPosition.x, objectCenter.y + offsetPosition.y, objectCenter.z);
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
}

void S2SynthesizerCircle::draw()
{
    ofSetColor(255, 255, 255, int(alpha));
    ofCircle(position, radius);
}

bool S2SynthesizerCircle::isDone()
{
    return done;
}

void S2SynthesizerCircle::onCompleteTween(float* arg)
{
    Tweenzor::removeTween(&alpha);
    done = true;
}
