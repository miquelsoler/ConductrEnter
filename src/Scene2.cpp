//
//  Scene2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene2.h"

#include "S2DrumsAmoeba.h"
#include "S2Drums.h"
#include "S2NoiseSphere.h"
#include "S2Synthesizer.h"
#include "S2ExampleObject.h"
#include "S2CircleParticles.h"
#include "S2NoisePlexus.h"

#include "Defaults.h"

#include "SettingsManager.h"
#include "TUIOHandler.h"

const unsigned int NUM_OBJECTS = 6;

#pragma mark - Object creation

///--------------------------------------------------------------
Scene2::Scene2(const string &name, bool singleSetup, ScreenSetup *screenSetup) : BaseScene(name, singleSetup, screenSetup)
{
    num_objects = NUM_OBJECTS;
    viewWidth = (ofGetWidth() / num_objects);
    viewHeight = ofGetHeight();

    clipHeight = viewHeight / SettingsManager::getInstance().abletonArtistOffset;

    // Initialitze OSC
    string host = SettingsManager::getInstance().abletonHost;
    unsigned int senderPort = SettingsManager::getInstance().abletonSenderPort;
    unsigned int receiverPort = SettingsManager::getInstance().abletonReceiverPort;
    abletonManager = new AbletonManager(host, senderPort, receiverPort, num_objects);

    artistOffset = SettingsManager::getInstance().abletonArtistOffset;

    // Create scene objects
    float viewOrigin;
    string objectsPath = "settings/scene2/";

    bool enableDemoObjects;
#ifdef OF_DEBUG
    enableDemoObjects = SettingsManager::getInstance().debugEnableDemoObjects;
#else
    enableDemoObjects = SettingsManager::getInstance().releaseEnableDemoObjects;
#endif

    for (unsigned int i = 0; i < num_objects; i++)
    {
        viewOrigin = i * viewWidth;
        S2BaseObj *object = NULL;
        if (!enableDemoObjects)
        {
            switch (i)
            {
                case 0:
                    object = new S2Drums(num_objects, i, viewOrigin, viewWidth, objectsPath + "drums.xml");
                    break;
                case 1:
                    object = new S2NoiseSphere(num_objects, i, viewOrigin, viewWidth, objectsPath + "noise_sphere.xml");
                    break;
                case 2:
                    object = new S2DrumsAmoeba(num_objects, i, viewOrigin, viewWidth, objectsPath + "drums_amoeba.xml");
                    break;
                case 3:
                    object = new S2Synthesizer(num_objects, i, viewOrigin, viewWidth, objectsPath + "synthesizer.xml");
                    break;
                case 4:
                    object = new S2CircleParticles(num_objects, i, viewOrigin, viewWidth, objectsPath + "circleParticle.xml");
                    break;
                case 5:
                    object = new S2NoisePlexus(num_objects, i, viewOrigin, viewWidth, objectsPath + "plexus.xml");
                    break;
                default:
                    break;
            }
        }
        else
        {
            object = new S2ExampleObject(num_objects, i, viewOrigin, viewWidth, objectsPath + "example.xml");
        }

        if (!object) continue;
        objects.push_back(object);
        ofAddListener(abletonManager->eventsVolumeChanged[i], object, &S2BaseObj::volumeChanged);
        ofAddListener(abletonManager->eventsClipPositionChanged[i], object, &S2BaseObj::clipPositionChanged);
    }
}

///--------------------------------------------------------------
Scene2::~Scene2()
{
    for (int i = 0; i < num_objects; ++i)
        delete objects[i];

    delete abletonManager;
}

#pragma mark - OF main calls

///--------------------------------------------------------------
void Scene2::setup()
{
    if (!enableBackgroundVideos) return;

    if (!videoPlayer.isLoaded()) videoPlayer.loadMovie("video/Loop_background_Playground_v3.mov");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
}

///--------------------------------------------------------------
void Scene2::update()
{
    if (enableBackgroundVideos)
    {
        if (videoPlayer.isPlaying())
            videoPlayer.update();
    }

    abletonManager->update();
    for (unsigned int i = 0; i < num_objects; ++i)
        objects[i]->update();
}

///--------------------------------------------------------------
void Scene2::updateEnter()
{
    currentClipIndex = (artistIndex * artistOffset) + (artistOffset/2) + SettingsManager::getInstance().abletonFirstClipIndex;

    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene2::tuioReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene2::tuioDragged);

    ofAddListener(TUIOHandler::getInstance().eventTouchDownCursor, this, &Scene2::tuioReceiverPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUpCursor, this, &Scene2::tuioReceiverReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDragCursor, this, &Scene2::tuioReceiverDragged);

    // Request tempo in order to set it on objects
    ofAddListener(abletonManager->eventTempoChanged, this, &Scene2::tempoChanged);
    abletonManager->requestTempo();
    abletonManager->requestVolumeUpdates();
    abletonManager->requestGridUpdates();

    // Stop all playing clips, just in case (for demo purposes)
    abletonManager->stopAll();

    if (enableBackgroundVideos)
        videoPlayer.play();

    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->setup();

    leaveSceneTimer.setup(SettingsManager::getInstance().scene2TimerMilliseconds);

    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene2::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene2::tuioPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchUp, this, &Scene2::tuioReleased);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDrag, this, &Scene2::tuioDragged);

    ofRemoveListener(TUIOHandler::getInstance().eventTouchDownCursor, this, &Scene2::tuioReceiverPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchUpCursor, this, &Scene2::tuioReceiverReleased);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDragCursor, this, &Scene2::tuioReceiverDragged);

    ofRemoveListener(abletonManager->eventTempoChanged, this, &Scene2::tempoChanged);

    abletonManager->stopAll();

    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene2::draw()
{
    BaseScene::drawPre();

    if (enableBackgroundVideos) {
        if (videoPlayer.isPlaying()) {
            videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
        }
    }

    ofEnableBlendMode(OF_BLENDMODE_ADD);

    for (unsigned int i = 0; i < num_objects; ++i)
        objects[i]->draw();

    ofDisableBlendMode();

    bool showTUIOCursors;
#ifdef OF_DEBUG
    showTUIOCursors = SettingsManager::getInstance().debugShowTUIOCursors;
#else
    showTUIOCursors = SettingsManager::getInstance().releaseShowTUIOCursors;
#endif

    if (showTUIOCursors)
    {
        ofxTuioClient *tuioClient = TUIOHandler::getInstance().tuioClient;
        tuioClient->drawCursors(0.5, 1, 0);
    }

    BaseScene::drawPost();
}

///--------------------------------------------------------------
void Scene2::exit()
{
}

///--------------------------------------------------------------
void Scene2::setArtistIndex(int _artistIndex)
{
    artistIndex = _artistIndex;
}

#pragma mark - Interaction handling

///--------------------------------------------------------------
/**
*  If coming from mouse (cursorId == NULL)
*      If object not yet picked
*          Try to pick it (coords inside object)
*          If picked
*              Play Ableton clip
*              Animate object
*          Else
*              Do nothing
*  If coming from TUIO (cursorId != NULL):
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
void Scene2::handlePress(InteractionSource interactionSource, int x, int y, TuioCursor *cursor)
{
    if ((x < 0) || (x >= ofGetWidth())) return;
    if ((y < 0) || (y >= viewHeight)) return;

    int pressedObjectIndex = getObjectIndexAtX(x);
    S2BaseObj *object = objects[pressedObjectIndex];

    bool isPicked = object->getIsPicked();

    if (interactionSource == InteractionSourceMouse)
    {
        if (isPicked) return;
        if (!object->pick(x, y)) return;

        mouseObjectIndex = pressedObjectIndex;

        // Play Ableton clip
        int track = pressedObjectIndex;
        abletonManager->playClip(currentClipIndex, track);
        // Animate the touched object
        object->play();
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
            object->play();

            // Add TUIO cursor
            object->addCursor(cursor);
        }
        else
        {
            object->addCursor(cursor);
        }
    }
}

///--------------------------------------------------------------
void Scene2::handleRelease(InteractionSource interactionSource, int x, int y, int cursorId)
{
    if ((x < 0) || (x >= ofGetWidth())) return;
    if ((y < 0) || (y >= viewHeight)) return;

    int pressedObjectIndex;

    if (interactionSource == InteractionSourceMouse)
    {
        pressedObjectIndex = mouseObjectIndex;
    }
    else // Coming from TUIO
    {
        pressedObjectIndex = getObjectIndetWithCursor(cursorId);
        if (pressedObjectIndex == -1)
        {
            return;
        }
    }

    S2BaseObj *object = objects[pressedObjectIndex];

    // Remove TUIO cursors and disable pinch
    object->removeLastCursor();
    object->disableColorImage();
    if (!object->getIsPicked()) return;
    object->unpick();

    // Stop Ableton clip
    int track = pressedObjectIndex;
    abletonManager->stopClip(currentClipIndex, track);

    // Stop animating the touched object
    object->stop();
}

///--------------------------------------------------------------
void Scene2::handleDrag(InteractionSource interactionSource, int x, int y, int cursorId)
{
    if ((x < 0) || (x >= ofGetWidth())) return;
    if ((y < 0) || (y >= viewHeight)) return;

    unsigned int pressedObjectIndex = getObjectIndexAtX(x);

    S2BaseObj *object = objects[pressedObjectIndex];

    if (!object->getIsPicked()) return;

    // Send message to Ableton

    int pressedClipIndex = getClipIndexAtY(y) + (artistIndex * artistOffset) + SettingsManager::getInstance().abletonFirstClipIndex;
    if (pressedClipIndex != currentClipIndex)
    {
        int track = pressedObjectIndex;

        abletonManager->stopClip(currentClipIndex, track);
        currentClipIndex = (unsigned int)pressedClipIndex;
        // Play Ableton clip
        abletonManager->playClip(currentClipIndex, track);
    }

    // Position object (only if mouse, or if TUIO and cursor is the first one -to avoid crazy repositioning-
    TuioCursor *firstCursor = object->getFirstCursor();

    bool mouseCondition = (interactionSource == InteractionSourceMouse);
    bool tuioCondition = (interactionSource == InteractionSourceTuio) && ((firstCursor == NULL) || (firstCursor->getCursorID() == cursorId));

    if (mouseCondition || tuioCondition)
    {
        object->setPositionFromScreenCoords(x, y);
    }

//        // Update Ableton track
//
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
}

#pragma mark - Touch events

///--------------------------------------------------------------
void Scene2::tuioPressed(ofTouchEventArgs &touch)
{
    TuioCursor *myCursor = makeCursor(touch.id, touch.x, touch.y);

    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    handlePress(InteractionSourceTuio, int(screenCoords.x), int(screenCoords.y), myCursor);
}

///--------------------------------------------------------------
void Scene2::tuioReleased(ofTouchEventArgs &touch)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    handleRelease(InteractionSourceTuio, int(screenCoords.x), int(screenCoords.y), touch.id);
}

///--------------------------------------------------------------
void Scene2::tuioDragged(ofTouchEventArgs &touch)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(touch.x, touch.y);
    handleDrag(InteractionSourceTuio, int(screenCoords.x), int(screenCoords.y), touch.id);
}

///--------------------------------------------------------------
void Scene2::tuioReceiverPressed(TUIOReceiverEvent &cursor)
{
    TuioCursor *myCursor = makeCursor(cursor.sourceId, cursor.sessionId, cursor.cursorId,
                                      cursor.x, cursor.y, cursor.xSpeed, cursor.ySpeed, cursor.motionAccel);

    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(cursor.x, cursor.y);
    handlePress(InteractionSourceTuio, int(screenCoords.x), int(screenCoords.y), myCursor);
}

///--------------------------------------------------------------
void Scene2::tuioReceiverReleased(TUIOReceiverEvent &cursor)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(cursor.x, cursor.y);
    handleRelease(InteractionSourceTuio, int(screenCoords.x), int(screenCoords.y), cursor.cursorId);
}

///--------------------------------------------------------------
void Scene2::tuioReceiverDragged(TUIOReceiverEvent &cursor)
{
    ofVec2f screenCoords = TUIOHandler::tuioToScreenCoords(cursor.x, cursor.y);
    handleDrag(InteractionSourceTuio, int(screenCoords.x), int(screenCoords.y), cursor.cursorId);
}

#pragma mark - Mouse events

///--------------------------------------------------------------
void Scene2::mouseDragged(int x, int y, int button)
{
    handleDrag(InteractionSourceMouse, x, y);
}

///--------------------------------------------------------------
void Scene2::mousePressed(int x, int y, int button)
{
    handlePress(InteractionSourceMouse, x, y);
}

///--------------------------------------------------------------
void Scene2::mouseReleased(int x, int y, int button)
{
    handleRelease(InteractionSourceMouse, x, y);
}

#pragma mark - Some listeners

///--------------------------------------------------------------
void Scene2::tempoChanged(float &newTempo)
{
#ifdef OF_DEBUG
    cout << "New tempo is " << newTempo << endl;
#endif
}

///--------------------------------------------------------------
void Scene2::windowResized(ofResizeEventArgs &args)
{
    viewWidth = ofGetWidth() / num_objects;
    viewHeight = ofGetHeight();
    clipHeight = viewHeight / SettingsManager::getInstance().abletonArtistOffset;
}

#pragma mark - Helper methods

///--------------------------------------------------------------
unsigned int Scene2::getObjectIndexAtX(int x)
{
    return (unsigned int)(floor(x / viewWidth));
}

unsigned int Scene2::getObjectIndetWithCursor(int cursorId)
{
    bool found = false;
    int objectIndex = -1;
    for (int i=0; i<num_objects && !found; i++)
    {
        list<TuioCursor *> objectCursors = objects[i]->getCursors();
        list<TuioCursor *>::iterator it;
        for (it = objectCursors.begin(); it != objectCursors.end() && !found; ++it)
        {
            found = ((*it)->getCursorID() == cursorId);
            if (found) objectIndex = i;
        }
    }

    return objectIndex;
}

///--------------------------------------------------------------
unsigned int Scene2::getClipIndexAtY(int y)
{
    return (unsigned int)(floor(y / clipHeight));
}

///--------------------------------------------------------------
TuioCursor *Scene2::makeCursor(int cursorId, float x, float y)
{
    long sessionId = 0;
    TuioCursor *cursor = new TuioCursor(sessionId, cursorId, x, y);
    return cursor;
}

///--------------------------------------------------------------
TuioCursor *Scene2::makeCursor(int sourceId, int sessionId, int cursorId, float x, float y, float xSpeed, float ySpeed, float motionAccel)
{
    TuioCursor *cursor = new TuioCursor(sessionId, cursorId, x, y);
    return cursor;
}

///--------------------------------------------------------------
void Scene2::switchShowGUI()
{
    for(int i=0;i<objects.size();i++)
        objects[i]->showGUI = !objects[i]->showGUI;
}
