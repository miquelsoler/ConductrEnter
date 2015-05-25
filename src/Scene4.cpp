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
    objects.push_back(new S4Object2());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
    objects.push_back(new S4Object1());
//    objects.push_back(new S4Object3());
//    objects.push_back(new S4Object4());
//    objects.push_back(new S4Object5());
//    objects.push_back(new S4Object6());
//    objects.push_back(new S4Object7());
//    objects.push_back(new S4Object8());

    num_objects = objects.size();

}

Scene4::~Scene4()
{
    for (int i=0; i<num_objects; ++i)
        delete objects[i];
}

#pragma mark - OF main calls

void Scene4::setup()
{
    cout << "Called setup for scene 4" << endl;
    // Init viewport settings for every object

    const float viewWidth = ofGetWidth() / num_objects;
    float viewOrigin;
    for (int i=0; i<num_objects; ++i)
    {
        viewOrigin = i * viewWidth;
        objects[i]->initialize(viewOrigin, viewWidth);
    }

    // Setup every object
    
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
