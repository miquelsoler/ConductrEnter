//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene2.h"
#include "of3dGraphics.h"

void Scene2::setup()
{
    sphere.setRadius(ofGetWidth() * .12);
}

void Scene2::update()
{
    // Coordinates and rotation settings

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    sphere.setPosition(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 0);
    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0.0, 1.0, 0.0);
    
}

void Scene2::drawScene()
{
    // Draw sphere wireframe

    ofNoFill();
    ofSetColor(255, 127, 127);
    sphere.drawWireframe();

    // Back to default color

    ofSetColor(255);
}

void Scene2::exit()
{
}
