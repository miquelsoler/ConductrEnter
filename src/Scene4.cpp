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

/**/ // OSC
#define OSC_HOST "localhost"
#define OSC_PORT 9030
#define ABLETON_CLIP 4

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

    viewWidth = ofGetWidth() / num_objects;
    float viewOrigin;

    for (int i=0; i<num_objects; ++i)
    {
        ostringstream settingsPath;
        settingsPath << "settings/scene4/obj" << i+1 << ".xml";
        viewOrigin = i * viewWidth;
        objects[i]->initialize(viewOrigin, viewWidth, settingsPath.str());
    }

    /**/ // OSC
    oscSender.setup(OSC_HOST, OSC_PORT);
    for (int i=0; i<num_objects; i++)
    {
        // Stop all playing clips, just in case (for demo purposes)
        objectIsPlaying.push_back(false);
        ofxOscMessage m;
        m.setAddress("/live/stop/clip");
        m.addIntArg(i);
        m.addIntArg(ABLETON_CLIP);
        oscSender.sendMessage(m);
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
//    cout << "Mouse moved for scene 4" << endl;
}

void Scene4::mouseDragged(int x, int y, int button)
{
//    cout << "Mouse dragged for scene 4" << endl;
}

void Scene4::mousePressed(int x, int y, int button)
{
    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    if (pressedObjectIndex != -1)
    {
        int track = pressedObjectIndex;

        ofxOscMessage m;
        string address = !(objectIsPlaying[pressedObjectIndex]) ? "/live/play/clip" : "/live/stop/clip";
        m.setAddress(address);
        // Session view -> col number (track)
        m.addIntArg(track);
        // Session view -> row number (clip)
        m.addIntArg(ABLETON_CLIP);
        oscSender.sendMessage(m);
        objectIsPlaying[pressedObjectIndex] = !objectIsPlaying[pressedObjectIndex];

        cout << "Play track " << pressedObjectIndex << " - clip " << ABLETON_CLIP << endl;
    }
//    cout << "Mouse pressed for scene 4" << endl;
}

void Scene4::mouseReleased(int x, int y, int button)
{
//    cout << "Mouse released for scene 4" << endl;
}

#pragma mark - Helper methods

int Scene4::getObjectIndexAtPosition(int x, int y)
{
    int result = -1;

    bool found = false;
    float objOriginX;
    for (int i=0; i<num_objects; i++ && !found)
    {
        objOriginX = objects[i]->getViewOriginX();
        if (x>=objOriginX && x<objOriginX+viewWidth) {
            result = i;
            found = true;
        }
    }

    return result;
}
