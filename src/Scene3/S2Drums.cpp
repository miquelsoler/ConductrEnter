//
//  S2Drums.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S2Drums.h"
#include "SettingsManager.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S2Drums::S2Drums(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2Drums::loadSettings()
{
    if (settingsPath.empty()) return;
    S2BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.add(sphereResolution.set("Resolution", 16, 8,128));
    sphereResolution.addListener(this, &S2Drums::sphereResolutionChanged);
    gui.add(spherePointSize.set("Point Size", 1, 1.0, 10.0));
    gui.add(sphereVolumeScale.set("Volume Scale", 4, 1.0, 5.0));

    gui.loadFromFile(settingsPath);
}

#pragma mark - Basic object methods

///--------------------------------------------------------------
void S2Drums::setup()
{
    S2BaseObj::setup();

    float initialSphereRotation = 33.0f;
    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.rotate(initialSphereRotation, 0.0, 1.0, 0.0);
    bool enableVBO;
#ifdef OF_DEBUG
    enableVBO = SettingsManager::getInstance().debugEnableVBO;
#else
    enableVBO = SettingsManager::getInstance().releaseEnableVBO;
#endif

    sphere.setUseVbo(enableVBO);
    transitioningSphere.setPosition(objPosition);
    transitioningSphere.setRadius(radius);
    transitioningSphere.rotate(initialSphereRotation, 0.0, 1.0, 0.0);

    camera.setTarget(sphere);

    vertexDistance = 1;

    trianglesOriginal.clear();
    noises.clear();

    if (isFirstSetup)
    {
        trianglesOriginal = sphere.getMesh().getUniqueFaces();
        trianglesCurrent = sphere.getMesh().getUniqueFaces();

        int size = (int) trianglesOriginal.size();
        for (int i=0; i<size; i++) {
            noises.push_back(ofRandom(1));
        }
    }

    isFirstSetup = false;

    Tweenzor::resetAllTweens();
}

#pragma mark - Object states

///--------------------------------------------------------------
void S2Drums::initInactive()
{
    float delay = 0.0f;
    float duration = 0.2f;
    Tweenzor::add(&sphereGrayColor, 255.0f, 120.0f, delay, duration, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereGrayColor);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S2Drums::onCompleteInactive);

    volumeCircleRadius = 0;
    volumeCircleAlpha = 0;
    maxVolumeCircleRadius = 50;
    maxVolumeCircleAlpha = 250;

    sphereGrayColor = 255.0f;
}

void S2Drums::onCompleteInactive(float* arg)
{
    if (!shouldChangeState)
        initInactive();
    else
        changeState();
}

void S2Drums::updateInactive()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
    updateActive(); // Delete this line if it needs a custom update
}

void S2Drums::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------

void S2Drums::initTransitioning()
{
    float delay = 0.0f;
    float duration = 0.3f;
    Tweenzor::add(&transitioningCircleRadius, whiteCircleRadius, whiteCircleRadius*4, delay, duration, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&transitioningCircleRadius);
    Tweenzor::addCompleteListener(tween, this, &S2Drums::onCompleteTransitioning);

    Tweenzor::add(&transitioningCircleAlpha, 250.0f, 0.0f, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitioningSphereScale, 1.0f, 1.5f, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitioningSphereAlpha, 250.0f, 0.0f, delay, duration, EASE_IN_OUT_SINE);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
}

void S2Drums::onCompleteTransitioning(float* arg)
{
    changeState();
}

void S2Drums::updateTransitioning()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
//    updateActive(); // Delete this line if it needs a custom update
}

void S2Drums::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2Drums::initActive()
{
    trianglesCurrent = sphere.getMesh().getUniqueFaces();
}

void S2Drums::updateActive()
{
    ofVec3f triangleNormal;
    int size = (int) trianglesOriginal.size();

    for (int i=0; i<size; i++) {
        triangleNormal = trianglesOriginal[i].getFaceNormal();
        for (int j=0; j<3; j++) {
            trianglesCurrent[i].setVertex(j, trianglesOriginal[i].getVertex(j) - (vertexDistance* noises[i])*triangleNormal);
        }
    }

    sphere.getMesh().setFromTriangles(trianglesCurrent);
}

void S2Drums::drawActive()
{
    camera.begin(viewRectangle);
    {
        ofSetColor(int(sphereGrayColor));
        glPointSize(spherePointSize);
        sphere.drawVertices();

        // Draw transitioning circle and sphere exlosion
        if (currentState == S3ObjStateTransitioning)
        {
            // Sphere
            ofSetColor(255, 255, 255, int(transitioningSphereAlpha));
            transitioningSphere.setScale(transitioningSphereScale);
            transitioningSphere.drawVertices();

            // Circle
            ofFill();
            ofSetColor(255, 255, 255, int(transitioningCircleAlpha));
            ofCircle(objPosition.x, objPosition.y, 0, transitioningCircleRadius);
        }

        // Draw volume circle
        if (currentState == S3ObjStateActive)
        {
            ofFill();
            ofSetColor(255, 255, 255, int(volumeCircleAlpha));
            ofCircle(objPosition.x, objPosition.y, 0, volumeCircleRadius);
        }

        drawPinchCircle();
        drawPinchColor();
        drawWhiteCircle();
        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S2Drums::volumeChanged(float &newVolume)
{
    if (currentState == S3ObjStateActive)
    {
        float toRadius = ofMap(newVolume,0.0,1.0,0, maxVolumeCircleRadius);
        float toAlpha = ofMap(newVolume,0.0,1.0,0, maxVolumeCircleAlpha);
        volumeCircleRadius = toRadius;
        volumeCircleAlpha = toAlpha;

        vertexDistance = (newVolume*0.7f) * exp(newVolume * sphereVolumeScale);
    }
    else
    {
        vertexDistance = 1;
    }
}

//--------------------------------------------------------------
void S2Drums::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);
    sphere.setPosition(objPosition);
    transitioningSphere.setPosition(objPosition);
}

///--------------------------------------------------------------
void S2Drums::windowResized(ofResizeEventArgs &args)
{
    S2BaseObj::windowResized(args);

    sphere.setPosition(objPosition);
    transitioningSphere.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(sphere);
}

///--------------------------------------------------------------
void S2Drums::sphereResolutionChanged(int &newSphereResolution)
{
    sphere.setResolution(newSphereResolution);
    transitioningSphere.setResolution(newSphereResolution);

    trianglesOriginal.clear();
    noises.clear();

    trianglesOriginal = sphere.getMesh().getUniqueFaces();
    trianglesCurrent = sphere.getMesh().getUniqueFaces();

    int size = (int) trianglesOriginal.size();
    for (int i=0; i<size; i++) {
        noises.push_back(ofRandom(1));
    }
}
