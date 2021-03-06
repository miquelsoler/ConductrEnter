//
//  S2BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S2BaseObj.h"
#include "SettingsManager.h"
#include "Defaults.h"


// Arc loop
const int LOOP_RESOLUTION = 128;
const int ANGLE_OFFSET = 90;
const int AXIS_LENGTH = 10;


#pragma mark - Initialization

///--------------------------------------------------------------
S2BaseObj::S2BaseObj(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath)  : BaseObject(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    camera.disableMouseInput();

    colorImage.loadImage("objects/colorGradientConductrCircleFeather.png");
    colorImage.setAnchorPercent(0.5f, 0.5f);

    circleImage.loadImage("objects/color_circle.png");
    circleImage.setAnchorPercent(0.5f, 0.5f);

    colorImageAlphaMin = SettingsManager::getInstance().colorCircleAlphaMin;
    colorImageAlphaMax = SettingsManager::getInstance().colorCircleAlphaMax;
    colorImageAlpha = colorImageAlphaMin;

    settingsPath = _settingsPath;

    isFirstSetup = true;

    ofAddListener(eventChangeState, this, &S2BaseObj::changeState);

#ifdef OF_DEBUG
    showGUI = SettingsManager::getInstance().debugShowGUI;
#else
    showGUI = SettingsManager::getInstance().releaseShowGUI;
#endif
}

///--------------------------------------------------------------
void S2BaseObj::initSharedSettings()
{
    gui.setup("Settings", settingsPath);
    gui.add(activated.set("activate",true));
    gui.add(camDistance.set("Camera_Distance", 0, 0, 1000));
    gui.add(loopRadius.set("Loop_Radius", 0, 0, 100));
    gui.add(loopInitialAngle.set("Loop_Initial_Angle", 0, 0, 360));
    gui.add(whiteCircleRadius.set("White_Circle_Radius", 40, 0, 30));
}

#pragma mark - Basic object methods

///--------------------------------------------------------------
void S2BaseObj::setup()
{
    radius = viewHalfWidth/5;
    objPosition.x = 0;
    objPosition.y = 0;
    
    camera.setNearClip(0.1f);
    camera.setFarClip(1000.0f);
    camera.setDistance(camDistance);

    gui.setPosition(viewOriginX+viewHalfWidth*0.7f, 0);

    loopAngle = 0;
    disableColorImage();

    currentState = nextState = S3ObjStateInactive;
    shouldChangeState = false;

    initInactive();
}

///--------------------------------------------------------------
void S2BaseObj::update()
{

    if(activated)
    {
        camera.setDistance(camDistance);

        switch(currentState)
        {
            case S3ObjStateInactive:
                updateInactive();
                break;
            case S3ObjStateTransitioning:
                updateTransitioning();
                break;
            case S3ObjStateActive:
                updateActive();
                break;
        }
    }
}

///--------------------------------------------------------------
void S2BaseObj::draw()
{
    if (activated)
    {
        switch(currentState)
        {
            case S3ObjStateInactive:
                drawInactive();
                break;
            case S3ObjStateTransitioning:
                drawTransitioning();
                break;
            case S3ObjStateActive:
                drawActive();
                break;
        }
    }

    if (showGUI)
        gui.draw();
}

///--------------------------------------------------------------
void S2BaseObj::drawLoop()
{
    ofSetLineWidth(2);
    ofSetColor(ofColor::white);

    // Draw white loop arc (only if current angle is not 0)
    if ((currentState == S3ObjStateActive) && (int(loopAngle) != 0))
    {
        // Draw loop arc
        loopArc.clear();
        int convertedAngle = ANGLE_OFFSET + 360 - loopInitialAngle;
        float angleStart = convertedAngle - loopAngle;
        float angleEnd = convertedAngle;
        loopArc.arc(objPosition, loopRadius, loopRadius, angleStart, angleEnd, LOOP_RESOLUTION);
        loopArc.draw();
    }

    // Draw axis
    // Top
    ofPushMatrix();
    ofTranslate(objPosition.x, objPosition.y); // Move to center of object
    ofRotateZ(360- loopInitialAngle); // Rotate line according to the angle
    ofTranslate(0, loopRadius); // Move it so that it starts at the arc perimeter
    ofLine(0, 0, 0, AXIS_LENGTH);
    ofPopMatrix();
    // Bottom
    ofPushMatrix();
    ofTranslate(objPosition.x, objPosition.y); // Move to center of object
    ofRotateZ(360- loopInitialAngle); // Rotate line according to the angle
    ofTranslate(0, -loopRadius); // Move it so that it starts at the arc perimeter
    ofLine(0, 0, 0, -AXIS_LENGTH);
    ofPopMatrix();
}

///--------------------------------------------------------------
void S2BaseObj::drawWhiteCircle()
{
    ofFill();
    ofSetColor(ofColor::white);
    ofCircle(objPosition.x, objPosition.y, 0, whiteCircleRadius);
}

///--------------------------------------------------------------
void S2BaseObj::drawPinchCircle()
{
    ofFill();
    ofSetColor(255, 2255, 255, colorImageAlpha);
    circleImage.draw(objPosition, circleImageSize, circleImageSize);
}

///--------------------------------------------------------------
void S2BaseObj::drawPinchColor()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofSetColor(255*colorImageAlpha, 255*colorImageAlpha, 255*colorImageAlpha, colorImageAlpha);
    colorImage.draw(objPosition, 200, 200);
    ofDisableBlendMode();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    glDisable(GL_ALPHA_TEST);
}

///--------------------------------------------------------------
void S2BaseObj::windowResized(ofResizeEventArgs &args)
{
    viewWidth = args.width / sceneNumObjects;
    viewHalfWidth = viewWidth / 2.0f;
    viewHalfHeight = args.height / 2.0f;
    viewOriginX = sceneObjectIndex * viewWidth;
    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, args.height);

    gui.setPosition(viewOriginX+viewHalfWidth*0.4f, 0);

    camera.setDistance(camDistance);
}

///--------------------------------------------------------------
bool S2BaseObj::pick(int screenX, int screenY)
{
    ofVec3f centerScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    ofVec3f perimeterScreenCoords = camera.worldToScreen(ofVec3f(objPosition.x, objPosition.y - radius*2, objPosition.z), viewRectangle);

    float distToPerimeter = ofDistSquared(centerScreenCoords.x, centerScreenCoords.y, perimeterScreenCoords.x, perimeterScreenCoords.y);
    float distToScreen = ofDistSquared(centerScreenCoords.x, centerScreenCoords.y, screenX, screenY);

    isPicked = distToScreen <= distToPerimeter;

    return isPicked;
}

///--------------------------------------------------------------
void S2BaseObj::unpick()
{
    isPicked = false;
}

///--------------------------------------------------------------
bool S2BaseObj::getIsPicked()
{
    return isPicked;
}

///--------------------------------------------------------------
void S2BaseObj::disableColorImage()
{
    circleImageSize = 0.0f;
    colorImageAlpha = 0.0f;
}

///--------------------------------------------------------------
void S2BaseObj::setPositionFromScreenCoords(int screenX, int screenY)
{
    ofVec3f objScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    objScreenCoords.x = screenX;
    objScreenCoords.y = screenY;

    float oldX = objPosition.x;

    objPosition = camera.screenToWorld(objScreenCoords, viewRectangle);

    xOffset = fabs(objPosition.x);
    float minXOffset = SettingsManager::getInstance().colorMinXOffset;
    if (xOffset >= minXOffset)
    {
        xOffset = (xOffset >= minXOffset) ? xOffset-minXOffset : 0;
        circleImageSize = whiteCircleRadius + xOffset;
        if (circleImageSize > radius * 1.3f)
            circleImageSize = radius * 1.3f;

        colorImageAlpha = (unsigned int) ofMap(xOffset, 0, whiteCircleRadius * 4.0f, colorImageAlphaMin, colorImageAlphaMax, true);
    }
    else
    {
        xOffset = 0;
    }

    objPosition.x = oldX;
}

#pragma mark - Play/stop messages + state management

///--------------------------------------------------------------
void S2BaseObj::play()
{
    loopAngle = 0;
    switch(currentState)
    {
        case S3ObjStateInactive:
            nextState = S3ObjStateTransitioning;
            shouldChangeState = true;
            break;
        case S3ObjStateTransitioning:
        case S3ObjStateActive:
            break;
    }
}

///--------------------------------------------------------------
void S2BaseObj::stop()
{
    loopAngle = 0;
    switch(currentState)
    {
        case S3ObjStateActive:
        case S3ObjStateTransitioning:
            nextState = S3ObjStateInactive;
            shouldChangeState = true;
            changeState();
            break;
        case S3ObjStateInactive:
            break;
    }
}

///--------------------------------------------------------------
void S2BaseObj::changeState()
{
    currentState = nextState;
    shouldChangeState = false;
    switch(currentState)
    {
        case S3ObjStateInactive:
            initInactive();
            break;
        case S3ObjStateTransitioning:
            initTransitioning();
            break;
        case S3ObjStateActive:
            initActive();
            break;
    }
}

#pragma mark - Ableton events

///--------------------------------------------------------------
void S2BaseObj::clipPositionChanged(float &newPosition)
{
    loopAngle = ofMap(newPosition, 0.0f, 1.0f, 0.0f, 360.0f);
}

float S2BaseObj::getXOffset()
{
    return xOffset;
}

float S2BaseObj::getRadius()
{
    return radius;
}

#pragma mark - TUIO

void S2BaseObj::addCursor(TuioCursor *cursor)
{
    cursors.push_back(cursor);
}

void S2BaseObj::removeAllCursors()
{
    while (!cursors.empty())
    {
        delete cursors.front();
        cursors.pop_front();
    }
}

TuioCursor *S2BaseObj::getFirstCursor()
{
    if (cursors.empty()) return NULL;
    return cursors.front();
}

list<TuioCursor *> S2BaseObj::getCursors()
{
    return cursors;
}
