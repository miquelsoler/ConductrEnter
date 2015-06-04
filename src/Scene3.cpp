//
//  Scene3.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene3.h"

#include "S3Object1.h"
#include "S3Object2.h"
#include "S3Object3.h"
#include "S3Object4.h"
#include "S3Object5.h"
#include "S3Object6.h"

#include "SettingsManager.h"

#define ABLETON_CLIP 4

#pragma mark - Object creation

Scene3::Scene3(const string& name) : BaseScene(name)
{
    cout << "SCENE 4 constructor" << endl;
    objects.push_back(new S3Object1());
    objects.push_back(new S3Object1());
    objects.push_back(new S3Object1());
    objects.push_back(new S3Object1());
    objects.push_back(new S3Object1());
    objects.push_back(new S3Object1());

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

    // Initialitze OSC

    string abletonHost = SettingsManager::getInstance().oscAbletonHost;
    unsigned int abletonPort = SettingsManager::getInstance().oscAbletonPort;

    oscSender.setup(abletonHost, abletonPort);

    // Stop all playing clips, just in case (for demo purposes)
    for (int i=0; i<num_objects; i++)
    {
        objectTrackIsPlaying.push_back(false);
        ofxOscMessage m;
        m.setAddress("/live/stop/clip");
        m.addIntArg(i);
        m.addIntArg(ABLETON_CLIP);
        oscSender.sendMessage(m);
    }
}

Scene3::~Scene3()
{
    for (int i=0; i<num_objects; ++i)
        delete objects[i];
}

#pragma mark - OF main calls

void Scene3::setup()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->setup();
}

void Scene3::update()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->update();
}

void Scene3::drawScene()
{
    for (unsigned int i=0; i<num_objects; ++i)
        objects[i]->draw();
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
    float windowHeight = ofGetHeight();

    if ((y>=0) && (y<windowHeight)) {

        // Send OSC message
        
        int pressedObjectIndex = getObjectIndexAtPosition(x, y);

        ofxOscMessage m;

        // /live/master/device (int track, int device, int parameter,int value) -> Sets parameter on device on track number track to value

        string address = "/live/master/device";
        m.setAddress(address);
        m.addIntArg(0);
        m.addIntArg(pressedObjectIndex+1);
        int value;
        float halfHeight = windowHeight/2.0f;
        if ((y>=0) && (y<halfHeight)) {
            value = ofMap(y, halfHeight-1, 0, 0, 127);
        } else {
            value = ofMap(y, halfHeight, windowHeight, 0, 127);
        }
        m.addIntArg(value);
        oscSender.sendMessage(m);
        cout << "Message: " << m.getAddress() << "-" << m.getArgAsInt32(0) << "-" << m.getArgAsInt32(1) << "-" << m.getArgAsInt32(2) << endl;

        // Move object vertically

        float newY = ofMap(y, 0, windowHeight, windowHeight, 0);
        objects[pressedObjectIndex]->setY(newY);
    }
}

void Scene3::mousePressed(int x, int y, int button)
{
    if (button == OF_MOUSE_BUTTON_RIGHT) {

        // Play/pause the clip ABLETON_CLIP at track determinated by the touched object

        int pressedObjectIndex = getObjectIndexAtPosition(x, y);

        int track = pressedObjectIndex;

        ofxOscMessage m;
        string address = !(objectTrackIsPlaying[pressedObjectIndex]) ? "/live/play/clip" : "/live/stop/clip";
        m.setAddress(address);
        // Session view -> col number (track)
        m.addIntArg(track);
        // Session view -> row number (clip)
        m.addIntArg(ABLETON_CLIP);
        oscSender.sendMessage(m);
        objectTrackIsPlaying[pressedObjectIndex] = !objectTrackIsPlaying[pressedObjectIndex];

        // Animate (or not) the touched object
        objects[pressedObjectIndex]->setAnimated(objectTrackIsPlaying[pressedObjectIndex]);
    }
}

void Scene3::mouseReleased(int x, int y, int button)
{
    // Resets the value to zero

    // /live/master/device (int track, int device, int parameter,int value) -> Sets parameter on device on track number track to value

    int pressedObjectIndex = getObjectIndexAtPosition(x, y);

    ofxOscMessage m;
    string address = "/live/master/device";
    m.setAddress(address);
    m.addIntArg(0);
    m.addIntArg(pressedObjectIndex+1);
    int value = 0;
    m.addIntArg(value);
    oscSender.sendMessage(m);
}

#pragma mark - Helper methods

int Scene3::getObjectIndexAtPosition(int x, int y)
{
    return floor(x/viewWidth);
}
