//
//  Scene1.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#include "Scene1.h"
#include "of3dGraphics.h"

void Scene1::setup()
{
    if (!videoPlayer.isLoaded()) videoPlayer.loadMovie("video/scene1_bg.mov");

    videoPlayer.play();
}

void Scene1::update()
{
    videoPlayer.update();
}

void Scene1::drawScene()
{
    videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void Scene1::exit()
{
    videoPlayer.stop();
    videoPlayer.firstFrame();
}