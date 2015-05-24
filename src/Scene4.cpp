//
//  Scene4.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene4.h"

#include "S4Object1.h"
#include "S4Object2.h"
#include "S4Object3.h"
#include "S4Object4.h"
#include "S4Object5.h"
#include "S4Object6.h"
#include "S4Object7.h"
#include "S4Object8.h"

#pragma mark - Object creation

Scene4::Scene4(const string& name) : BaseScene(name)
{
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object2());
    objects.push_back(new S4Object3());
    objects.push_back(new S4Object4());
    objects.push_back(new S4Object5());
    objects.push_back(new S4Object6());
    objects.push_back(new S4Object7());
    objects.push_back(new S4Object8());

    num_objects = objects.size();

    // Init viewport settings for every object

    const float viewWidth = ofGetWidth() / num_objects;
    float viewOrigin;
    for (int i=0; i<num_objects; ++i)
    {
        viewOrigin = i * viewWidth;
        objects[i]->initialize(viewOrigin, viewWidth);
    }
}

Scene4::~Scene4()
{
    for (int i=0; i<num_objects; ++i)
        delete objects[i];
}

#pragma mark - OF main calls

void Scene4::setup()
{
    ofLog(OF_LOG_NOTICE, "Scene 4 setup");

    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->setup();

//    vector<S4BaseObj*>::const_iterator it;
//    for (it = objects.begin(); it != objects.end(); ++it)
//    {
//        (*it)->setup();
//    }

//    fbo1Cylinder.setRadius(ofGetWidth() * .09);
//    fbo1Cylinder.setHeight(ofGetHeight() * 0.65);
//
//    fbo2Cylinder.setRadius(ofGetWidth() * .09);
//    fbo2Cylinder.setHeight(ofGetHeight() * 0.65);
//
//    fbo1.allocate(ofGetWidth()/2, ofGetHeight());
//    fbo2.allocate(ofGetWidth()/2, ofGetHeight());
}

void Scene4::update()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->update();
//    updateFbo1();
//    updateFbo2();
}

void Scene4::drawScene()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->draw();

    // Draw box wireframe

    ofSetColor(127, 127, 255);

//    fbo1.draw(0,0);
//    fbo2.draw(ofGetWidth()/2,0);

    // Back to default color

    ofSetColor(255);
}

void Scene4::exit()
{
}

//void Scene4::updateFbo1()
//{
//    // Coordinates and rotation settings
//
//    float spinX = sin(ofGetElapsedTimef()*.35f);
//    float spinY = cos(ofGetElapsedTimef()*.075f);
//
//    fbo1Cylinder.rotate(spinX, 1.0, 0.0, 0.0);
//    fbo1Cylinder.rotate(spinY, 0.0, 1.0, 0.0);
//
//    fbo1.begin();
//    ofBackground(127,30,30);
//    ofPushMatrix();
//    ofTranslate(fbo1.getWidth()/2, fbo1.getHeight()/2);
//    fbo1Cylinder.drawWireframe();
//    ofPopMatrix();
//    fbo1.end();
//}
//
//void Scene4::updateFbo2()
//{
//    // Coordinates and rotation settings
//
//    float spinX = sin(ofGetElapsedTimef()*.35f);
//    float spinY = cos(ofGetElapsedTimef()*.075f);
//
//    fbo2Cylinder.rotate(spinX, 1.0, 0.0, 0.0);
//    fbo2Cylinder.rotate(spinY, 0.0, 1.0, 0.0);
//
//    fbo2.begin();
//    ofBackground(30,127,30);
//    ofPushMatrix();
//    ofTranslate(fbo2.getWidth()/2, fbo2.getHeight()/2);
//    fbo2Cylinder.drawWireframe();
//    ofPopMatrix();
//    fbo2.end();
//}