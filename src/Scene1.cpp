//
//  Scene1.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 21/5/15.
//
//

#include "Scene1.h"
#include "of3dGraphics.h"

void Scene1::setup()
{
    if (!videoPlayer.isLoaded()) videoPlayer.loadMovie("video/scene1_bg.mov");

    if (!videoPlayer.isPlaying()) videoPlayer.play();
    videoPlayer.setVolume(0);
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

#pragma mark - Touch events

void Scene1::mouseMoved(int x, int y)
{
}

void Scene1::mouseDragged(int x, int y, int button)
{
}

void Scene1::mousePressed(int x, int y, int button)
{
}

void Scene1::mouseReleased(int x, int y, int button)
{
}
