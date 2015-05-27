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

#pragma mark - Object creation

Scene4::Scene4(const string& name) : BaseScene(name)
{
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());

    num_objects = objects.size();

    // Initialize viewport and parameters for every object

    const float viewWidth = ofGetWidth() / num_objects;
    float viewOrigin;

    for (int i=0; i<num_objects; ++i)
    {
        ostringstream settingsPath;
        settingsPath << "settings/scene4/obj" << i+1 << ".xml";
        viewOrigin = i * viewWidth;
        objects[i]->initialize(viewOrigin, viewWidth, settingsPath.str());
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
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->setup();
}

void Scene4::update()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->update();
}

void Scene4::drawScene()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->draw();
}

void Scene4::exit()
{
}

#pragma mark - Touch events

void Scene4::mouseMoved(int x, int y)
{
    cout << "Mouse moved for scene 4" << endl;
}

void Scene4::mouseDragged(int x, int y, int button)
{
    cout << "Mouse dragged for scene 4" << endl;
}

void Scene4::mousePressed(int x, int y, int button)
{
    cout << "Mouse pressed for scene 4" << endl;
}

void Scene4::mouseReleased(int x, int y, int button)
{
    cout << "Mouse released for scene 4" << endl;
}
