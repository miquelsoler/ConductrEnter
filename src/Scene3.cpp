//
//  Scene3.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene3.h"

void Scene3::setup()
{
    box.set(ofGetWidth() * .2);
}

void Scene3::update()
{
    // Coordinates and rotation settings

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    box.setPosition(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 0);
    box.rotate(spinX, 1.0, 0.0, 0.0);
    box.rotate(spinY, 0.0, 1.0, 0.0);
    
}

void Scene3::drawScene()
{
    // Draw box wireframe

    ofNoFill();
    ofSetColor(127, 255, 127);
    box.drawWireframe();

    // Back to default color

    ofSetColor(255);
}

void Scene3::exit()
{
}
