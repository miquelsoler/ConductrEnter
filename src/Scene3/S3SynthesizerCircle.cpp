//
// Created by Miquel Àngel Soler on 22/6/15.
//

#include "S3SynthesizerCircle.h"
#include "ofxTweenzor.h"

S3SynthesizerCircle::S3SynthesizerCircle(ofPoint objectCenter, ofPoint _offsetPosition, float _radius)
{
    offsetPosition = _offsetPosition;
    position = ofPoint(objectCenter.x + offsetPosition.x, objectCenter.y + offsetPosition.y, objectCenter.z);
    radius = _radius;
    alpha = 255.0f;

    done = false;

    Tweenzor::add(&alpha, 255.0f, 0.0f, 0.0f, 1.0f, EASE_LINEAR);
    Tween *tween = Tweenzor::getTween(&alpha);
    Tweenzor::addCompleteListener(tween, this, &S3SynthesizerCircle::onCompleteTween);
}

S3SynthesizerCircle::~S3SynthesizerCircle()
{
}

void S3SynthesizerCircle::update(ofPoint objectCenter)
{
    position = ofPoint(objectCenter.x + offsetPosition.x, objectCenter.y + offsetPosition.y, objectCenter.z);
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
}

void S3SynthesizerCircle::draw()
{
    ofSetColor(255, 255, 255, int(alpha));
    ofCircle(position, radius);
}

bool S3SynthesizerCircle::isDone()
{
    return done;
}

void S3SynthesizerCircle::onCompleteTween(float* arg)
{
    Tweenzor::removeTween(&alpha);
    done = true;
}
