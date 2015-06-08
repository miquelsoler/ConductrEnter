//
//  S3Object2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3Object2.h"

const unsigned int RESOLUTION = 3;
const float BEAT_FREQUENCY = 500; // milliseconds

#pragma mark - Initialization

S3Object2::S3Object2(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

void S3Object2::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.loadFromFile(settingsPath);
}

#pragma mark - Basic object methods

void S3Object2::setup()
{
    S3BaseObj::setup();
    
    icoSphere1.setRadius(radius);
    icoSphere1.setResolution(RESOLUTION);
    icoSphere1.setPosition(objPosition);
    icoSphere1.rotate(45, 0.0, 1.0, 0.0);

    icoSphere2.setRadius(radius);
    icoSphere2.setResolution(RESOLUTION);
    icoSphere1.setPosition(objPosition);
    icoSphere2.rotate(-45, 0.0, 1.0, 0.0);

    camera.setTarget(icoSphere1);

    icoTriangles1 = icoSphere1.getMesh().getUniqueFaces();
    icoTriangles2 = icoSphere2.getMesh().getUniqueFaces();

    beatTimer.setup(BEAT_FREQUENCY);
    beatTimer.start(true);
    ofAddListener(beatTimer.TIMER_COMPLETE, this, &S3Object2::timerCompleteHandler);
}

void S3Object2::update()
{
    S3BaseObj::update();

    beatTimer.update();
    icoSphere1.rotate(-0.2, 1.0, 1.0, 0.0);
    icoSphere2.rotate(0.2, 1.0, 0.0, 0.0);

    vector<ofMeshFace> currentIcoTriangles1 = icoSphere1.getMesh().getUniqueFaces();
    vector<ofMeshFace> currentIcoTriangles2 = icoSphere1.getMesh().getUniqueFaces();
    ofVec3f triangleNormal;

    int size = icoTriangles1.size();
    for (int i=0; i<size; i++)
    {
        triangleNormal = icoTriangles1[i].getFaceNormal();
        for (int j=0; j<3; j++)
        {
            currentIcoTriangles1[i].setVertex(j, currentIcoTriangles1[i].getVertex(j) + 0.5 * triangleNormal);
        }
    }

    for (int i=0; i<size; i++)
    {
        triangleNormal = icoTriangles2[i].getFaceNormal();
        for (int j=0; j<3; j++)
        {
            currentIcoTriangles2[i].setVertex(j, currentIcoTriangles1[i].getVertex(j) + 0.5 * triangleNormal);
        }
    }

    icoSphere1.getMesh().setFromTriangles(currentIcoTriangles1);
    icoSphere2.getMesh().setFromTriangles(currentIcoTriangles2);
}

void S3Object2::draw()
{
    S3BaseObj::draw();

    camera.begin(viewRectangle);

    icoSphere1.drawVertices();
    icoSphere2.drawVertices();

    drawLoop();

    camera.end();
}

void S3Object2::windowResized(ofResizeEventArgs &args)
{
    S3BaseObj::windowResized(args);

    icoSphere1.setPosition(objPosition);
    icoSphere2.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(icoSphere1);
}

/**/ // OSC
void S3Object2::setY(float newY)
{
    float spherePosX = viewOriginX + viewHalfWidth;
    objPosition.set(spherePosX, newY);
    icoSphere1.setPosition(objPosition);
}

void S3Object2::timerCompleteHandler(int &args)
{
    vector<ofMeshFace> newIcoTriangles1(icoTriangles1);
    vector<ofMeshFace> newIcoTriangles2(icoTriangles2);
    ofVec3f triangleNormal;

    int size = icoTriangles1.size();
    for (int i=0; i<size; i++)
    {
        triangleNormal = icoTriangles1[i].getFaceNormal();
        for (int j=0; j<3; j++)
        {
            newIcoTriangles1[i].setVertex(j, icoTriangles1[i].getVertex(j) - triangleNormal*ofRandom(0,5));
        }
    }

    for (int i=0; i<size; i++)
    {
        triangleNormal = icoTriangles2[i].getFaceNormal();
        for (int j=0; j<3; j++)
        {
            newIcoTriangles2[i].setVertex(j, icoTriangles2[i].getVertex(j) - triangleNormal*ofRandom(0,5));
        }
    }

    icoSphere1.getMesh().setFromTriangles(newIcoTriangles1);
    icoSphere2.getMesh().setFromTriangles(newIcoTriangles2);

    cout << "BOOM! ";
}
