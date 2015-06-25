//
//  Scene1.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene1.h"

#include "SettingsManager.h"
#include "TUIOHandler.h"


///--------------------------------------------------------------
void Scene1::setup()
{
    /// VIDEO
    if (!videoPlayer.isLoaded()) videoPlayer.loadMovie("video/video_LoopIntroArtistes_v1.mov");

    videoPlayer.setLoopState(OF_LOOP_NONE);
    videoState = Loop;
    loopFrame = SettingsManager::getInstance().scene1IntroLoopFrame;

    float artistZoneWidth = 0.052083333;
    float artistZoneHeight = 0.03;
    artistsZone.push_back(Scene1ArtistZone(0.119791667, 0.668518519, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.227604167, 0.437037037, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.2640625, 0.57037037, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.3578125, 0.675925926, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.60625, 0.638888889, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.682291667, 0.462962963, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.7703125, 0.564814815, artistZoneWidth, artistZoneHeight));
    artistsZone.push_back(Scene1ArtistZone(0.834895833, 0.42962963, artistZoneWidth, artistZoneHeight));
}

///--------------------------------------------------------------
void Scene1::update()
{
    switch (sceneState)
    {
        case SceneStateIntro:
            updateStateIntro();
            break;
        case SceneStateArtists:
            updateStateArtists();
    }
}

///--------------------------------------------------------------
void Scene1::updateEnter()
{
    sceneState = SceneStateIntro;

    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene1::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchDownCursor, this, &Scene1::tuioReceiverPressed);

    videoState = Loop;
    videoPlayer.play();

    BaseScene::updateEnter();
}

///--------------------------------------------------------------
void Scene1::updateExit()
{
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDown, this, &Scene1::tuioPressed);
    ofRemoveListener(TUIOHandler::getInstance().eventTouchDownCursor, this, &Scene1::tuioReceiverPressed);
    BaseScene::updateExit();
}

///--------------------------------------------------------------
void Scene1::updateStateIntro()
{
    videoPlayer.update();
    Tweenzor::update(int(ofGetElapsedTimeMillis()));

    switch(videoState)
    {
        case Loop: {
            // Loop back to first frame when finished the loop segment
            if (videoPlayer.getCurrentFrame() >= loopFrame) videoPlayer.firstFrame();
            break;
        }
        case StartExplode: {
            // Manually set video header's frame based on Tweenzor driven parameter videoHeaderFrame
            videoPlayer.setFrame(int(videoHeaderFrame));
            break;
        }
        case Exploding: {
            // When we reach the end of the video ... switch to Artists State
            if (videoPlayer.getCurrentFrame() >= videoPlayer.getTotalNumFrames())
            {
                sceneState = SceneStateArtists;
            }
            break;
        }
    }
}

///--------------------------------------------------------------
void Scene1::updateStateArtists()
{
}

///--------------------------------------------------------------
void Scene1::draw()
{
    BaseScene::drawPre();
    
    videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

#ifdef OF_DEBUG
    if (sceneState == SceneStateArtists)
    {
        float numArtists = artistsZone.size();
        for (int i=0; i<numArtists; i++)
            artistsZone[i].draw();
    }
#endif

    BaseScene::drawPost();
}

///--------------------------------------------------------------
void Scene1::exit()
{
    videoPlayer.stop();
    videoPlayer.firstFrame();
}

#pragma mark - Video handling

///--------------------------------------------------------------
void Scene1::skipIntro()
{
    if (videoState == Loop)
    {
        // set video paused and add a tweenzor on videoHeaderFrame to drive it to the "end point" in x seconds
        videoState = StartExplode;
        videoPlayer.setPaused(true);
        Tweenzor::add(&videoHeaderFrame, float(videoPlayer.getCurrentFrame()), float(loopFrame), 0.0f, 0.8f, EASE_OUT_EXPO);
        Tweenzor::addCompleteListener( Tweenzor::getTween(&videoHeaderFrame), this, &Scene1::onVideoComplete);
    }
}

///--------------------------------------------------------------
void Scene1::onVideoComplete(float* arg)
{
    videoState = Exploding;
    videoPlayer.play();
}

#pragma mark - Artists

///--------------------------------------------------------------
int Scene1::getTouchedArtistIndex(float percentX, float percentY)
{
    int result = -1; // -1 means NONE

    bool found = false;
    int artistIndex;
    vector<Scene1ArtistZone>::iterator it;

    for (int i=0; i<artistsZone.size() && !found; i++)
    {
        found = artistsZone[i].isCoordinateInside(percentX, percentY);
        if (found) artistIndex = i;
    }

    if (found) result=artistIndex;

    return result;
}

#pragma mark - Touch events

///--------------------------------------------------------------
void Scene1::handlePress(float x, float y)
{
    switch(sceneState)
    {
        case SceneStateIntro:
        {
            skipIntro();
            break;
        }
        case SceneStateArtists:
        {
            int artistIndex = getTouchedArtistIndex(x, y);
            if (artistIndex != -1)
                ofNotifyEvent(eventGoToArtist, artistIndex, this);
        }
    }
}

///--------------------------------------------------------------
void Scene1::tuioPressed(ofTouchEventArgs &touch)
{
    handlePress(touch.x, touch.y);
}

void Scene1::tuioReceiverPressed(TUIOReceiverEvent &cursor)
{
    handlePress(cursor.x, cursor.y);
}

void Scene1::mousePressed(int x, int y, int button)
{
    ofVec2f percentCoords = TUIOHandler::screenToTuioCoords(x, y);
    handlePress(percentCoords.x, percentCoords.y);
}

void Scene1::mouseMoved(int x, int y)
{
//    cout << "mouse moved (" << x << ", " << y << ")" << endl;
}
