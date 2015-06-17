//
//  Scene3.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene3.h"

#include "S3DrumsAmoeba.h"
#include "S3Drums.h"
#include "S3Object1.h"

#include "SettingsManager.h"
#include "TUIOHandler.h"

const unsigned int NUM_OBJECTS = 6;

#pragma mark - Object creation

///--------------------------------------------------------------
Scene3::Scene3(const string& name, bool singleSetup) : BaseScene(name, singleSetup)
{
    num_objects = NUM_OBJECTS;
    viewWidth = ofGetWidth() / num_objects;
    viewHeight = ofGetHeight();

    clipHeight = viewHeight / NUM_CLIPS;

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
                object = new S3DrumsAmoeba(num_objects, i, viewOrigin, viewWidth, objectsPath + "drums_amoeba.xml"); break;
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
    currentClipIndex = DEFAULT_CLIP;

    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene3::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene3::tuioReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene3::tuioDragged);

    // Request tempo in order to set it on objects
    ofAddListener(abletonManager->eventTempoChanged, this, &Scene3::tempoChanged);
    abletonManager->requestTempo();
    abletonManager->requestVolumeUpdates();

    // Stop all playing clips, just in case (for demo purposes)
    abletonManager->stopAll();

    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene3::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene3::tuioPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene3::tuioReleased);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene3::tuioDragged);

    ofRemoveListener(abletonManager->eventTempoChanged, this, &Scene3::tempoChanged);

    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene3::draw()
{
    BaseScene::drawPre();

    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->draw();

#ifdef OF_DEBUG
    if (SettingsManager::getInstance().debugShowTUIOCursors)
    {
        ofxTuioClient *tuioClient = TUIOHandler::getInstance().tuioClient;
        tuioClient->drawCursors(0.5, 1, 0);
    }
#endif

    BaseScene::drawPost();
}

///--------------------------------------------------------------
void Scene3::exit()
{
}

#pragma mark - Touch events

///--------------------------------------------------------------
void Scene3::tuioPressed(ofTouchEventArgs &touch)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    handlePress((int)screenCoords.x, (int)screenCoords.y, touch.id);
}

///--------------------------------------------------------------
void Scene3::tuioReleased(ofTouchEventArgs &touch)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    handleRelease((int)screenCoords.x, (int)screenCoords.y, touch.id);
}
///--------------------------------------------------------------
void Scene3::tuioDragged(ofTouchEventArgs &touch)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    handleDrag((int)screenCoords.x, (int)screenCoords.y, touch.id);
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
/**
 *  If coming from mouse (cursorId == -1)
 *      If object not yet picked
 *          Try to pick it (coords inside object)
 *          If picked
 *              Play Ableton clip
 *              Animate object
 *          Else
 *              Do nothing
 *  If coming from TUIO (cursorId >= 0):
 *      If object not yet picked
 *          Try to pick it (coords inside object)
 *          If picked
 *              Play Ableton clip
 *              Animate object
 *              Add TUIO cursor id to object
 *          Else
 *              Do nothing
 *      Else
 *          Don't pick it again
 *          Add TUIO cursor id to object
 *          Enable pinch
 */
void Scene3::handlePress(int x, int y, int cursorId)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtX(x);
    S3BaseObj *object = objects[pressedObjectIndex];

    bool isPicked = object->getIsPicked();

    if (cursorId == -1) // Coming from mouse
    {
        if (isPicked) return;
        if (!object->pick(x, y)) return;

        // Play Ableton clip
        int track = pressedObjectIndex;
        abletonManager->playClip(currentClipIndex, track);
        // Animate the touched object
        object->setAnimated(true);
    }
    else // Coming from TUIO
    {
        if (!isPicked)
        {
            if (!object->pick(x, y)) return;

            // Play Ableton clip
            int track = pressedObjectIndex;
            abletonManager->playClip(currentClipIndex, track);

            // Animate the touched object
            object->setAnimated(true);

            // Add TUIO cursor
            object->addCursor(cursorId);
            object->enablePinch(false);
        }
        else
        {   // Already picked: add cursor and enable pinch
            object->addCursor(cursorId);
            object->enablePinch(true);
        }
    }
}

///--------------------------------------------------------------
void Scene3::handleRelease(int x, int y, int cursorId)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtX(x);
    S3BaseObj *object = objects[pressedObjectIndex];

    // Remove TUIO cursors and disable pinch
    object->removeLastCursor();
    object->enablePinch(false);
    if (!object->getIsPicked()) return;
    object->unpick();

    // Stop Ableton clip
    int track = pressedObjectIndex;
    abletonManager->stopClip(currentClipIndex, track);

    // Stop animating the touched object
    object->setAnimated(false);
}

///--------------------------------------------------------------
void Scene3::handleDrag(int x, int y, int cursorId)
{
    if ((x<0) || (x>=ofGetWidth())) return;
    if ((y<0) || (y>=viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtX(x);
    S3BaseObj *object = objects[pressedObjectIndex];

    if (!object->getIsPicked()) return;

    if (!object->isPinchEnabled())
    {
        // Send message to Ableton

        int pressedClipIndex = getClipIndexAtY(y);
        if (pressedClipIndex != currentClipIndex)
        {
            currentClipIndex = pressedClipIndex;

            // Play Ableton clip
            int track = pressedObjectIndex;
            abletonManager->playClip(currentClipIndex, track);
        }

//        /**/
//        int device = 0;
//        int parameter = pressedObjectIndex + 1;
//        int value;
//        float halfHeight = viewHeight/2.0f;
//        if ((y>=0) && (y<halfHeight)) {
//            value = (int)ofMap(y, halfHeight-1, 0, 0, 127);
//        } else {
//            value = (int)ofMap(y, halfHeight, viewHeight, 0, 127);
//        }
//
//        abletonManager->setDeviceParameter(device, parameter, value);

        // Position object (only if mouse, or if TUIO and cursor is the first one -to avoid crazy repositioning-
        int firstCursorId = object->getFirstCursorId();
        if ((firstCursorId == -1) || (firstCursorId == cursorId))
            object->setPositionFromScreenCoords(x, y);
    }
    else
    {
        object->updatePinch();
    }
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
int Scene3::getObjectIndexAtX(int x)
{
    return int(floor(x/viewWidth));
}

///--------------------------------------------------------------
int Scene3::getClipIndexAtY(int y)
{
    return int(floor(y/clipHeight));
}

///--------------------------------------------------------------
void Scene3::windowResized(ofResizeEventArgs &args)
{
    float viewWidthMargin = viewWidth/4;
    viewWidth = ofGetWidth() / num_objects;
    viewHeight = ofGetHeight();
}
