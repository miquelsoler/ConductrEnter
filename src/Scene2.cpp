//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

#include "Scene2.h"
#include "of3dGraphics.h"

void Scene2::setup()
{
    ofBackground(0, 127, 0);
}

void Scene2::draw()
{
    ofSetColor(180);
    ofNoFill();
    ofDrawCylinder(1, 10);
}
