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

#include "SettingsManager.h"
#include "TUIOHandler.h"

const unsigned int NUM_OBJECTS = 6;
const unsigned int ABLETON_CLIP = 4;

#pragma mark - Object creation

///--------------------------------------------------------------
Scene3::Scene3(const string& name, bool singleSetup) : BaseScene(name, singleSetup)
{
    num_objects = NUM_OBJECTS;
    viewWidth = ofGetWidth() / num_objects;
    viewHeight = ofGetHeight();

    // Initialitze OSC
    string host = SettingsManager::getInstance().abletonHost;
    unsigned int senderPort = SettingsManager::getInstance().abletonSenderPort;
    unsigned int receiverPort = SettingsManager::getInstance().abletonReceiverPort;
    abletonManager = new AbletonManager(host, senderPort, receiverPort, num_objects);

    // Create scene objects
    float viewOrigin;
    string objectsPath = "settings/scene3/";
    for (unsigned int i=0; i<NUM_OBJECTS; i++)
    {
        viewOrigin = i * viewWidth;
        S3BaseObj *object = NULL;
        switch(i)
        {
            case 0:
                object = new S3Drums(num_objects, i, viewOrigin, viewWidth, objectsPath + "drums.xml"); break;
            case 1:
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml"); break;
            case 2:
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml"); break;
            case 3:
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml"); break;
            case 4:
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml"); break;
            case 5:
                object = new S3Object1(num_objects, i, viewOrigin, viewWidth, objectsPath + "obj1.xml"); break;
            default:
                break;
        }
        if (object)
        {
            objects.push_back(object);
            ofAddListener(abletonManager->eventsVolumeChanged[i], object, &S3BaseObj::volumeChanged);
        }
    }

    // Request tempo in order to set it on objects
    ofAddListener(abletonManager->eventTempoChanged, this, &Scene3::tempoChanged);
    abletonManager->requestTempo();
    abletonManager->requestVolumeUpdates();

    // Stop all playing clips, just in case (for demo purposes)
    abletonManager->stopAll();
}

///--------------------------------------------------------------
Scene3::~Scene3()
{
    for (int i=0; i<num_objects; ++i)
        delete objects[i];

    delete abletonManager;
}

#pragma mark - OF main calls

///--------------------------------------------------------------
void Scene3::setup()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->setup();
}

///--------------------------------------------------------------
void Scene3::update()
{
    abletonManager->update();
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->update();
}

///--------------------------------------------------------------
void Scene3::updateEnter()
{
    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene3::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene3::tuioReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene3::tuioDragged);
    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene3::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene3::tuioPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene3::tuioReleased);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene3::tuioDragged);
    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene3::draw()
{
    BaseScene::drawPre();

    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->draw();

    BaseScene::drawPost();
}

///--------------------------------------------------------------
void Scene3::exit()
{
}

#pragma mark - Touch events

///--------------------------------------------------------------
void Scene3::tuioPressed(ofVec2f &coords)
{
    ofVec2f screenCoords = tuioToScreenCoords(coords);
    handlePress((int)screenCoords.x, (int)screenCoords.y);
}

///--------------------------------------------------------------
void Scene3::tuioReleased(ofVec2f &coords)
{
    ofVec2f screenCoords = tuioToScreenCoords(coords);
    handleRelease((int)screenCoords.x, (int)screenCoords.y);
}
///--------------------------------------------------------------
void Scene3::tuioDragged(ofVec2f &coords)
{
    ofVec2f screenCoords = tuioToScreenCoords(coords);
    handleDrag((int)screenCoords.x, (int)screenCoords.y);
}

#pragma mark - Mouse events

///--------------------------------------------------------------
void Scene3::mouseDragged(int x, int y, int button)
{
    handleDrag(x, y);
}

///--------------------------------------------------------------
void Scene3::mousePressed(int x, int y, int button)
{
    handlePress(x, y);
}

///--------------------------------------------------------------
void Scene3::mouseReleased(int x, int y, int button)
{
    handleRelease(x, y);
}

#pragma mark - Interaction handling

///--------------------------------------------------------------
void Scene3::handlePress(int x, int y)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    if (!objects[pressedObjectIndex]->pick(x, y)) return;

    int track = pressedObjectIndex;
    abletonManager->playClip(ABLETON_CLIP, track);

    // Animate (or not) the touched object
    objects[pressedObjectIndex]->setAnimated(true);
}

///--------------------------------------------------------------
void Scene3::handleRelease(int x, int y)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    if (!objects[pressedObjectIndex]->pick(x, y)) return;

    objects[pressedObjectIndex]->unpick();

    int track = pressedObjectIndex;
    abletonManager->stopClip(ABLETON_CLIP, track);

    // Animate (or not) the touched object
    objects[pressedObjectIndex]->setAnimated(false);
}

///--------------------------------------------------------------
void Scene3::handleDrag(int x, int y)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtPosition(x, y);
    if (!objects[pressedObjectIndex]->getIsPicked()) return;

    // Send OSC message

    int device = 0;
    int parameter = pressedObjectIndex + 1;
    int value;
    float halfHeight = viewHeight/2.0f;
    if ((y>=0) && (y<halfHeight)) {
        value = (int)ofMap(y, halfHeight-1, 0, 0, 127);
    } else {
        value = (int)ofMap(y, halfHeight, viewHeight, 0, 127);
    }

    abletonManager->setDeviceParameter(device, parameter, value);

    objects[pressedObjectIndex]->setPositionFromScreenCoords(x, y);
}

#pragma mark - Helper methods

///--------------------------------------------------------------
void Scene3::tempoChanged(float &newTempo)
{
#ifdef OF_DEBUG
    cout << "New tempo is " << newTempo << endl;
#endif
}

///--------------------------------------------------------------
int Scene3::getObjectIndexAtPosition(int x, int y)
{
    return (int)floor(x/viewWidth);
}

///--------------------------------------------------------------
void Scene3::windowResized(ofResizeEventArgs &args)
{
    viewWidth = ofGetWidth() / num_objects;
    viewHeight = ofGetHeight();
}
