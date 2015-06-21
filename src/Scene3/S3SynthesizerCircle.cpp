//
// Created by Miquel Àngel Soler on 22/6/15.
//

#include "S3SynthesizerCircle.h"

void S3SynthesizerCircle::draw()
{
    ofSetColor(255, 255, 255, alpha);
    ofCircle(position, radius);
}
