//
// Created by Miquel Àngel Soler on 22/6/15.
//

#pragma once

#ifndef __S3SynthesizerCircle_H_
#define __S3SynthesizerCircle_H_

#include "ofMain.h"

class S3SynthesizerCircle
{
public:

    S3SynthesizerCircle(ofPoint objectCenter, ofPoint offsetPosition, float radius);
    ~S3SynthesizerCircle();

    void draw();
    void update(ofPoint objectCenter);
    bool isDone();

private:

    ofPoint position;
    ofPoint offsetPosition;
    float   radius;
    float   alpha;
    bool    done;

    void onCompleteTween(float* arg);
};


#endif //__S3SynthesizerCircle_H_
