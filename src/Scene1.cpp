//
//  Scene1.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene1.h"

#include "SettingsManager.h"


//--------------------------------------------------------------
void Scene1::setup()
{
    /// VIDEO
    if (!videoPlayer.isLoaded()) videoPlayer.loadMovie("video/introLoop.mov");

    videoPlayer.setVolume(0);
    videoPlayer.setLoopState(OF_LOOP_NONE);
    videoState = 0;
    loopFrame = SettingsManager::getInstance().intro_loop_frame;

    /// TWEENZOR
    // must call this before adding any tweens
	Tweenzor::init();

}

//--------------------------------------------------------------
void Scene1::update()
{
    videoPlayer.update();
    Tweenzor::update( ofGetElapsedTimeMillis() );

    if(videoState==0)
    {
        // loop back to first frame when finised the loop segment
        if(videoPlayer.getCurrentFrame()>=loopFrame)
        {
            videoPlayer.firstFrame();
        }
    }
    else if (videoState == 1)
    {
        // manually set video header's frame based on tweenzor driven parameter videoHeaderFrame
        videoPlayer.setFrame(int(videoHeaderFrame));
    }
    else if (videoState == 2)
    {
        // when we reach the end of the video ... change to scene 2
        if(videoPlayer.getCurrentFrame()>=videoPlayer.getTotalNumFrames())
        {
#ifdef OF_DEBUG
            cout << " scene1 : Finished ! Bring me to scene 2 pls ! " << endl;
#endif
        }
    }

}

//--------------------------------------------------------------
void Scene1::updateEnter()
{
    if (isEnteringFirst())
    {
        videoState = 0;
        videoPlayer.play();
    }

    BaseScene::updateEnter();
}

//--------------------------------------------------------------
void Scene1::draw()
{
    BaseScene::drawPre();
    
    videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight() );
    
    BaseScene::drawPost();
}

//--------------------------------------------------------------
void Scene1::exit()
{
    videoPlayer.stop();
    videoPlayer.firstFrame();
}

#pragma mark - Touch events

//--------------------------------------------------------------
void Scene1::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void Scene1::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void Scene1::mousePressed(int x, int y, int button)
{
    // this should be updated not by a mouse press but from a TUIO event ...
    goAhead();
}

//--------------------------------------------------------------
void Scene1::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void Scene1::goAhead()
{
    if(videoState==0)
    {
        // set video paused and add a tweenzor on videoHeaderFrame to drive it to the "end point" in x seconds
        videoState = 1;
        videoPlayer.setPaused(true);
        Tweenzor::add(&videoHeaderFrame, float(videoPlayer.getCurrentFrame()), float(loopFrame), 0.0f, 0.8f,   EASE_OUT_EXPO);
        Tweenzor::addCompleteListener( Tweenzor::getTween(&videoHeaderFrame), this, &Scene1::onComplete);
    }
    
}

//--------------------------------------------------------------
void Scene1::onComplete(float* arg)
{
    videoState=2;
	videoPlayer.play();
}
