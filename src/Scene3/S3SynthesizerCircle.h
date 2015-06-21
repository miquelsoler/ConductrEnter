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

    ofPoint position;
    float radius;
    float alpha;

private:

    void drawCircle();
};


#endif //__S3SynthesizerCircle_H_
