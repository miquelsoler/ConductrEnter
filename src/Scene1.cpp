//
//  Scene1.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

#include "Scene1.h"
#include "of3dGraphics.h"

// Només necessari si cal afegir més codi al constructor. De moment queda al .h
//Scene1::Scene1(const string& name) : BaseScene(name)
//{
//    ofLog(OF_LOG_VERBOSE, "%s:%s", typeid(BaseScene).name(), __func__);
//}

void Scene1::setup()
{
    ofBackground(127, 0, 0);
    sphere.setRadius(ofGetWidth() * 0.1f);
}

void Scene1::draw()
{
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 255 * alpha);	// alpha member variable for fade in/out

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    sphere.setPosition(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 0.0f);
    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0, 1.0, 0.0);

    sphere.draw();
}
