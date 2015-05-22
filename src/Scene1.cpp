//
//  Scene1.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 21/5/15.
//
//

#include "Scene1.h"
#include "of3dGraphics.h"

Scene1::Scene1(const string& name) : BaseScene(name)
{
}

void Scene1::setup()
{
    if (!videoPlayer.isLoaded())
    {
        ofLog(OF_LOG_NOTICE, "Not loaded");
        videoPlayer.loadMovie("video/scene1_bg.mov");
    }
    videoPlayer.play();
}

void Scene1::update()
{
    videoPlayer.update();
}

void Scene1::draw()
{
    enableAlphaBlendingForFade();
    videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
    disableAlphaBlendingForFade();
}

void Scene1::exit()
{
    videoPlayer.stop();
    videoPlayer.firstFrame();
}