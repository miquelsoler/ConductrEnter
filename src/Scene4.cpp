//
//  Scene4.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene4.h"

void Scene4::setup()
{
    cylinder.setRadius(ofGetWidth() * .12);
    cylinder.setHeight(ofGetHeight() / 2);
}

void Scene4::update()
{
    // Coordinates and rotation settings

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    cylinder.setPosition(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 0);
    cylinder.rotate(spinX, 1.0, 0.0, 0.0);
    cylinder.rotate(spinY, 0.0, 1.0, 0.0);
    
}

void Scene4::drawScene()
{
    // Draw box wireframe

    ofNoFill();
    ofSetColor(127, 127, 255);
    cylinder.drawWireframe();

    // Back to default color

    ofSetColor(255);
}

void Scene4::exit()
{
}
