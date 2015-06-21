//
//  S3Drums.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S3Drums.h"

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

    // Custom object settings go here

    gui.add(sphereResolution.set("Resolution", 16, 8,128));
    sphereResolution.addListener(this, &S3Drums::sphereResolutionChanged);
    gui.add(spherePointSize.set("Point Size", 1, 1.0, 10.0));

    gui.loadFromFile(settingsPath);
}

#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3Drums::setup()
{
    S3BaseObj::setup();

    float initialSphereRotation = 33.0f;
    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.rotate(initialSphereRotation, 0.0, 1.0, 0.0);
    transitioningSphere.setPosition(objPosition);
    transitioningSphere.setRadius(radius);
    transitioningSphere.rotate(initialSphereRotation, 0.0, 1.0, 0.0);

    camera.setTarget(sphere);

    vertexDistance = 1;

    trianglesOriginal.clear();
    trianglesCurrent.clear();
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
void S3Drums::initInactive()
{
    float delay = 0.0f;
    float duration = 0.7f;
    Tweenzor::add(&sphereGrayColor, 255.0f, 120.0f, delay, duration, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereGrayColor);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3Drums::onCompleteInactive);

    sphereGrayColor = 255.0f;
}

void S3Drums::onCompleteInactive(float* arg)
{
    if (!shouldChangeState)
        initInactive();
    else
        changeState();
}

void S3Drums::updateInactive()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    updateActive(); // Delete this line if it needs a custom update
}

void S3Drums::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------

void S3Drums::initTransitioning()
{
    float delay = 0.0f;
    float duration = 0.3f;
    Tweenzor::add(&transitioningCircleRadius, whiteCircleRadius, whiteCircleRadius*4, delay, duration, EASE_IN_OUT_SINE);
    Tween *tween1 = Tweenzor::getTween(&transitioningCircleRadius);
    Tweenzor::addCompleteListener(tween1, this, &S3Drums::onCompleteTransitioning);

    Tweenzor::add(&transitioningCircleAlpha, 250.0f, 0.0f, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitioningSphereScale, 1.0f, 1.5f, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitioningSphereAlpha, 250.0f, 0.0f, delay, duration, EASE_IN_OUT_SINE);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
}

void S3Drums::onCompleteTransitioning(float* arg)
{
    changeState();
}

void S3Drums::updateTransitioning()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
//    updateActive(); // Delete this line if it needs a custom update
}

void S3Drums::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S3Drums::initActive()
{

}

void S3Drums::updateActive()
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

void S3Drums::drawActive()
{
    camera.begin(viewRectangle);

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
        ofDisableLighting();
        ofSetColor(255, 255, 255, int(transitioningCircleAlpha));
        ofCircle(objPosition.x, objPosition.y, 0, transitioningCircleRadius);

    }

    drawWhiteCircle();
    if (pinchEnabled) drawPinchCircle();



    drawLoop();


    camera.end();
}

///--------------------------------------------------------------
void S3Drums::volumeChanged(float &newVolume)
{
    if (currentState == S3ObjStateActive)
    {
        vertexDistance = (newVolume*0.7f) * exp(newVolume * 3.0f);
    }
    else
    {
        vertexDistance = 1;
    }
}

//--------------------------------------------------------------
void S3Drums::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);
    sphere.setPosition(objPosition);
    transitioningSphere.setPosition(objPosition);
}

///--------------------------------------------------------------
void S3Drums::windowResized(ofResizeEventArgs &args)
{
    S3BaseObj::windowResized(args);

    sphere.setPosition(objPosition);
    transitioningSphere.setPosition(objPosition);

    camera.setPosition(objPosition);
    camera.setTarget(sphere);
}

///--------------------------------------------------------------
void S3Drums::sphereResolutionChanged(int &newSphereResolution)
{
    sphere.setResolution(newSphereResolution);
    transitioningSphere.setResolution(newSphereResolution);

    trianglesOriginal.clear();
    trianglesCurrent.clear();
    noises.clear();

    trianglesOriginal = sphere.getMesh().getUniqueFaces();
    trianglesCurrent = sphere.getMesh().getUniqueFaces();

    int size = (int) trianglesOriginal.size();
    for (int i=0; i<size; i++) {
        noises.push_back(ofRandom(1));
    }
}
