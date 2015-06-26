//
//  S2BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S2BaseObj.h"
#include "TUIOHandler.h"
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

    pinchImage.loadImage("objects/color_circle.png");
    pinchImage.setAnchorPercent(0.5f, 0.5f);

    pinchImageAlphaMin = SettingsManager::getInstance().pinchCircleAlphaMin;
    pinchImageAlphaMax = SettingsManager::getInstance().pinchCircleAlphaMax;
    pinchImageAlpha = pinchImageAlphaMin;

    settingsPath = _settingsPath;

    isFirstSetup = true;

    ofAddListener(eventChangeState, this, &S2BaseObj::changeState);
    
    // FBO
    //-----
    //ofFbo::allocate(int width, int height, int internalformat, int numSamples)
    fbo.allocate(FBO_WIDTH, FBO_HEIGHT, GL_RGBA32F_ARB, 1);

    fbo.begin();
    {
        ofClear(0,0,0,0);
    }
    fbo.end();
    
    showGUI = false;

}

///--------------------------------------------------------------
void S2BaseObj::initSharedSettings()
{
    gui.setup("Settings", settingsPath);
    gui.add(activate.set("activate",true));
    gui.add(camDistance.set("Camera_Distance", 0, 0, 600));
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

    currentState = nextState = S3ObjStateInactive;
    shouldChangeState = false;

    initInactive();
}

///--------------------------------------------------------------
void S2BaseObj::update()
{
    if(activate)
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
void S2BaseObj::drawIntoFbo()
{
    if(activate)
    {
    
        fbo.begin();
        
        //ofClear(0,0,(255/6)*sceneObjectIndex,128);
        ofClear(0,0,0,0);
        
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
        
        fbo.end();

    }
}

///--------------------------------------------------------------
void S2BaseObj::draw(int x,int y,int w,int h)
{
    if(activate)
    {

        fbo.draw(x,y,w,h);
    }

    if(showGUI)
    {
        if (SettingsManager::getInstance().debugShowGUI)
        {
            gui.draw();
        }
    }
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

void S2BaseObj::drawWhiteCircle()
{
    ofFill();
    ofDisableLighting();
    ofSetColor(ofColor::white);
    ofCircle(objPosition.x, objPosition.y, 0, whiteCircleRadius);
}

void S2BaseObj::drawPinchCircle()
{
    ofFill();
    ofDisableLighting();
    ofSetColor(255, 2255, 255, pinchImageAlpha);
    pinchImage.draw(objPosition, pinchImageSize, pinchImageSize);

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
void S2BaseObj::enablePinch(bool enable)
{
    pinchEnabled = enable;

    if (!pinchEnabled) return;

    if (cursorIds.size() <= 1)
    {
        pinchEnabled = false;
        return;
    }

    TuioCursor *cursor1 = cursorIds.front();
    TuioCursor *cursor2 = cursorIds.back();

    pinchInitialDist = TUIOHandler::getInstance().getDistBetweenCursors(cursor1, cursor2);

    pinchImageSize = whiteCircleRadius / 2;
}

///--------------------------------------------------------------
bool S2BaseObj::isPinchEnabled()
{
    return pinchEnabled;
}

///--------------------------------------------------------------
void S2BaseObj::updatePinch()
{
    if (!pinchEnabled) return;

    TuioCursor *cursor1 = cursorIds.front();
    TuioCursor *cursor2 = cursorIds.back();
    float pinchCurrentDist = TUIOHandler::getInstance().getDistBetweenCursors(cursor1, cursor2);

    float diff = pinchCurrentDist - pinchInitialDist;
    if (diff > 0)
    {
        pinchImageSize = whiteCircleRadius + diff/4;
        pinchImageAlpha = (unsigned int)ofMap(pinchCurrentDist, pinchInitialDist, pinchInitialDist*2.0f, pinchImageAlphaMin, pinchImageAlphaMax, true);
    }
}

///--------------------------------------------------------------
TuioCursor *S2BaseObj::getFirstCursor()
{
    if (cursorIds.empty()) return NULL;
    return cursorIds.front();
}

///--------------------------------------------------------------
TuioCursor *S2BaseObj::getLastCursor()
{
    if (cursorIds.empty()) return NULL;
    return cursorIds.back();
}

///--------------------------------------------------------------
void S2BaseObj::setPositionFromScreenCoords(int screenX, int screenY)
{
    ofVec3f objScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    objScreenCoords.y = screenY;

    float oldX = objPosition.x;

    objPosition = camera.screenToWorld(objScreenCoords, viewRectangle);
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

#pragma mark - TUIO

void S2BaseObj::addCursor(TuioCursor *cursor)
{
    cursorIds.push_back(cursor);
}

void S2BaseObj::removeLastCursor()
{
    if (cursorIds.empty()) return;
    TuioCursor *cursor = cursorIds.back();
    cursorIds.pop_back();
    delete cursor;
}