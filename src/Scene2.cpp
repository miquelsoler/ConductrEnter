//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene2.h"

void Scene2::setup()
{
    camera.scale = 500;
//    camera.disableMouseInput();

    sphere1.setRadius(ofGetWidth() * .12);
    sphere1.setPosition(50+ofGetWidth()/4.0f, ofGetHeight()/2.0f, 0);
    sphere2.setRadius(ofGetWidth() * .12);
    sphere2.setPosition((ofGetWidth()*3.0f/4.0f)-50, ofGetHeight()/2.0f, 0);

//    camera.setParent(sphere1);
    camera.setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2, 100));
//    camera.setTarget(ofPoint(0,0,0));

//    sphere.setRadius(viewWidth * .12);
//    objPosition.x = viewOriginX + viewHalfWidth;
//    objPosition.y = viewHalfHeight;
//    sphere.setPosition(objPosition);
//
//    camera.setPosition(objPosition);
//    camera.setTarget(sphere);
//    camera.setDistance(camDistance);
}

void Scene2::update()
{
    // Coordinates and rotation settings

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    sphere1.rotate(spinX, 1.0, 0.0, 0.0);
    sphere1.rotate(spinY, 0.0, 1.0, 0.0);

    sphere2.rotate(spinX, 1.0, 0.0, 0.0);
    sphere2.rotate(spinY, 0.0, 1.0, 0.0);
}

void Scene2::draw()
{
    ofRectangle viewport;
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = ofGetWidth();
    viewport.height = ofGetHeight();
    camera.begin(viewport);
//    camera.begin(viewRectangle);

    BaseScene::drawPre();

    // Draw sphere wireframe

    ofNoFill();
    ofSetColor(255, 127, 127);
    sphere1.drawWireframe();
    sphere2.drawWireframe();

    // Back to default color

    ofSetColor(255);

    BaseScene::drawPost();

    camera.end();
}

void Scene2::exit()
{
}

#pragma mark - Touch events

void Scene2::mouseMoved(int x, int y)
{
}

void Scene2::mouseDragged(int x, int y, int button)
{
}

void Scene2::mousePressed(int x, int y, int button)
{
}

void Scene2::mouseReleased(int x, int y, int button)
{
}
