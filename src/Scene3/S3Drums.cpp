//
//  S3Drums.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S3Drums.h"

const unsigned int RESOLUTION = 2;

#pragma mark - Initialization

///--------------------------------------------------------------
S3Drums::S3Drums(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3Drums::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    gui.loadFromFile(settingsPath);
}

#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3Drums::setup()
{
    S3BaseObj::setup();

    Tweenzor::init();
    
    sphere1.setRadius(radius);
    sphere1.setResolution(RESOLUTION);
    sphere1.setPosition(objPosition);
    sphere1.rotate(45, 0.0, 1.0, 0.0);

    sphere2.setRadius(radius);
    sphere2.setResolution(RESOLUTION);
    sphere2.setPosition(objPosition);
    sphere2.rotate(-45, 0.0, 1.0, 0.0);

    camera.setTarget(sphere1);

    trianglesOriginal1 = sphere1.getMesh().getUniqueFaces();
    trianglesCurrent1 = sphere1.getMesh().getUniqueFaces();
    trianglesOriginal2 = sphere2.getMesh().getUniqueFaces();
    trianglesCurrent2 = sphere2.getMesh().getUniqueFaces();

    vertexDistance = 1;

    int size = (int)trianglesOriginal1.size();
    noises1.clear();
    noises2.clear();
    for (int i=0; i<size; i++) {
        noises1.push_back(ofRandom(1));
        noises2.push_back(ofRandom(1));
    }
}

///--------------------------------------------------------------
void S3Drums::update()
{
    S3BaseObj::update();

    Tweenzor::update((int)ofGetElapsedTimeMillis());

    ofVec3f triangleNormal;
    int size = (int)trianglesOriginal1.size();

    for (int i=0; i<size; i++) {
        triangleNormal = trianglesOriginal1[i].getFaceNormal();
        for (int j=0; j<3; j++) {
            trianglesCurrent1[i].setVertex(j, trianglesOriginal1[i].getVertex(j) - (vertexDistance*noises1[i])*triangleNormal);
        }
        triangleNormal = trianglesOriginal2[i].getFaceNormal();
        for (int j=0; j<3; j++) {
            trianglesCurrent2[i].setVertex(j, trianglesOriginal2[i].getVertex(j) - (vertexDistance*noises2[i])*triangleNormal);
        }
    }

    sphere1.getMesh().setFromTriangles(trianglesCurrent1);
    sphere2.getMesh().setFromTriangles(trianglesCurrent2);

    sphere1.rotate(-0.2f, 1.0f, 1.0f, 0.0f);
    sphere2.rotate(0.5f, 1.0f, 0.0f, 0.0f);

//    ofVec3f wts = camera.worldToScreen(objPosition);
//    printf("worldToScreen: (%f,%f,%f)\n", wts.x, wts.y, wts.z);
}

///--------------------------------------------------------------
void S3Drums::volumeChanged(float &newVolume)
{
    vertexDistance = (newVolume*0.7) * exp(newVolume * 5);
}

///--------------------------------------------------------------
void S3Drums::draw()
{
    S3BaseObj::draw();

    camera.begin(viewRectangle);

    sphere1.drawVertices();
    sphere2.drawVertices();

    drawLoop();

    camera.end();
}

/////--------------------------------------------------------------
void S3Drums::setPositionFromScreenCoords(int screenX, int screenY)
{
    ofVec3f screenObj = camera.worldToScreen(objPosition, viewRectangle);
    screenObj.y = screenY;

    objPosition = camera.screenToWorld(screenObj, viewRectangle);

    sphere1.setPosition(objPosition);
    sphere2.setPosition(objPosition);
}

/////--------------------------------------------------------------
//void S3Drums::setY(float newY)
//{
//    float spherePosX = viewOriginX + viewHalfWidth;
//    objPosition.set(spherePosX, newY);
//    sphere1.setPosition(objPosition);
//    sphere2.setPosition(objPosition);
//}

///--------------------------------------------------------------
void S3Drums::windowResized(ofResizeEventArgs &args)
{
    S3BaseObj::windowResized(args);

    sphere1.setPosition(objPosition);
    sphere2.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(sphere1);
}
