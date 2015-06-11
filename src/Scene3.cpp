//
//  Scene3.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene3.h"

#include "S3Object1.h"
#include "S3Drums.h"
#include "S3Object3.h"
#include "S3Object4.h"
#include "S3Object5.h"
#include "S3Object6.h"

#include "SettingsManager.h"

const unsigned int NUM_OBJECTS = 6;
const unsigned int ABLETON_CLIP = 4;

#pragma mark - Object creation

Scene3::Scene3(const string& name, bool singleSetup) : BaseScene(name, singleSetup)
{
    num_objects = NUM_OBJECTS;
    viewWidth = ofGetWidth() / num_objects;
    viewHeight = ofGetHeight();

    // Create scene objects
    float viewOrigin;
    string objectsPath = "settings/scene3/";
    for (int i=0; i<NUM_OBJECTS; i++)
    {
//        ostringstream settingsPath;
//        settingsPath << "settings/scene3/obj" << i+1 << ".xml";
        viewOrigin = i * viewWidth;
        S3BaseObj *object;
        switch(i)
        {
            case 0: {
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml");
                break;
            }
            case 1: {
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml");
                break;
            }
            case 2: {
                object = new S3Drums(num_objects, i, viewOrigin, viewWidth, objectsPath + "drums.xml");
                break;
            }
            case 3: {
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml");
                break;
            }
            case 4: {
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml");
                break;
            }
            case 5: {
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml");
                break;
            }
        }
        objects.push_back(object);
    }

    // Initialitze OSC
    string host = SettingsManager::getInstance().abletonHost;
    unsigned int senderPort = SettingsManager::getInstance().abletonSenderPort;
    unsigned int receiverPort = SettingsManager::getInstance().abletonReceiverPort;
    abletonManager = new AbletonManager(host, senderPort, receiverPort);

    // Request tempo in order to set it on objects
    ofAddListener(abletonManager->tempoChanged, this, &Scene3::tempoChanged);
    abletonManager->requestTempo();
    abletonManager->requestVolumeUpdates();

    // Stop all playing clips, just in case (for demo purposes)
    abletonManager->stopAll();
    for (int i=0; i<num_objects; i++)
        objectIsPlaying.push_back(false);
}

Scene3::~Scene3()
{
    for (int i=0; i<num_objects; ++i)
        delete objects[i];

    delete abletonManager;
}

#pragma mark - OF main calls

void Scene3::setup()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->setup();
}

void Scene3::update()
{
    abletonManager->update();
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->update();
}

void Scene3::draw()
{
    BaseScene::drawPre();

    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->draw();

    BaseScene::drawPost();
}

void Scene3::exit()
{
}

#pragma mark - Touch events

void Scene3::mouseMoved(int x, int y)
{
}

void Scene3::mouseDragged(int x, int y, int button)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    objects[pressedObjectIndex]->isBeingTouched(x, y);

    // Send OSC message
    
    int device = 0;
    int parameter = pressedObjectIndex + 1;
    int value;
    float halfHeight = viewHeight/2.0f;
    if ((y>=0) && (y<halfHeight)) {
        value = ofMap(y, halfHeight-1, 0, 0, 127);
    } else {
        value = ofMap(y, halfHeight, viewHeight, 0, 127);
    }

    abletonManager->setDeviceParameter(device, parameter, value);

    // Move object vertically

    float newY = ofMap(y, 0, viewHeight, viewHeight, 0);
    objects[pressedObjectIndex]->setY(newY);
}

void Scene3::mousePressed(int x, int y, int button)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    objects[pressedObjectIndex]->isBeingTouched(x, y);

    if (button == OF_MOUSE_BUTTON_RIGHT) {

        // Play/pause the clip ABLETON_CLIP at track determinated by the touched object

        int pressedObjectIndex = getObjectIndexAtPosition(x, y);
        int track = pressedObjectIndex;

        if (!(objectIsPlaying[pressedObjectIndex])) {
            abletonManager->playClip(ABLETON_CLIP, track);
        } else {
            abletonManager->stopClip(ABLETON_CLIP, track);
        }

        objectIsPlaying[pressedObjectIndex] = !objectIsPlaying[pressedObjectIndex];

        // Animate (or not) the touched object
        objects[pressedObjectIndex]->setAnimated(objectIsPlaying[pressedObjectIndex]);
    }
}

void Scene3::mouseReleased(int x, int y, int button)
{
    // Resets /master/device value to zero
    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    abletonManager->setDeviceParameter(0, pressedObjectIndex+1, 0);
}

#pragma mark - Helper methods

int Scene3::getObjectIndexAtPosition(int x, int y)
{
    return floor(x/viewWidth);
}

void Scene3::windowResized(ofResizeEventArgs &args)
{
    viewWidth = ofGetWidth() / num_objects;
//    setup();
}

void Scene3::tempoChanged(float &newTempo)
{
#ifdef OF_DEBUG
    cout << "New tempo is " << newTempo << endl;
#endif
}

