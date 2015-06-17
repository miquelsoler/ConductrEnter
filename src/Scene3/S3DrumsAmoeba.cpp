//
//  S3DrumsAmoeba.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3DrumsAmoeba.h"

///--------------------------------------------------------------
S3DrumsAmoeba::S3DrumsAmoeba(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3DrumsAmoeba::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}

///--------------------------------------------------------------
void S3DrumsAmoeba::setup()
{
    S3BaseObj::setup();

//    sphere.setRadius(radius);
//    sphere.setPosition(objPosition);

//    camera.setTarget(sphere);
}

///--------------------------------------------------------------
void S3DrumsAmoeba::update()
{
    S3BaseObj::update();
}

///--------------------------------------------------------------
void S3DrumsAmoeba::volumeChanged(float &newVolume)
{
}

///--------------------------------------------------------------
void S3DrumsAmoeba::draw()
{
    S3BaseObj::draw();

    camera.begin(viewRectangle);

//    ofSetColor(ofColor::white);
//    sphere1.drawVertices();
//    sphere2.drawVertices();

    drawLoop();

    camera.end();}

///--------------------------------------------------------------
void S3DrumsAmoeba::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);
}

void S3DrumsAmoeba::windowResized(ofResizeEventArgs &args)
{
    S3BaseObj::windowResized(args);

//    sphere1.setPosition(objPosition);
//    sphere2.setPosition(objPosition);

    camera.setPosition(objPosition);
//    camera.setTarget(sphere1);
}
