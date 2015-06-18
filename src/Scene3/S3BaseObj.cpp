//
//  S3BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3BaseObj.h"
#include "TUIOHandler.h"
#include "SettingsManager.h"


// Arc loop
const int LOOP_RESOLUTION = 128;
const int ANGLE_OFFSET = 90;
const int AXIS_LENGTH = 6;


#pragma mark - Initialization

///--------------------------------------------------------------
S3BaseObj::S3BaseObj(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath)  : BaseObject(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    camera.disableMouseInput();

    pinchImage.loadImage("objects/color_circle.png");
    pinchImage.setAnchorPercent(0.5f, 0.5f);

    pinchImageAlphaMin = SettingsManager::getInstance().pinchCircleAlphaMin;
    pinchImageAlphaMax = SettingsManager::getInstance().pinchCircleAlphaMax;
    pinchImageAlpha = pinchImageAlphaMin;

    settingsPath = _settingsPath;
}

///--------------------------------------------------------------
void S3BaseObj::initSharedSettings()
{
    gui.setup("Settings", settingsPath);
    gui.add(camDistance.set("Camera_Distance", 0, 0, 600));
    gui.add(whiteCircleRadius.set("White_Circle_Radius", 40, 0, 30));
    gui.add(loopRadius.set("Loop_Radius", 0, 0, 100));
    gui.add(loopAngle.set("Loop_Angle", 0, 0, 720));
}

#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3BaseObj::setup()
{
    radius = viewHalfWidth/5;
    objPosition.x = 0;
    objPosition.y = 0;

    camera.setNearClip(0.1f);
    camera.setFarClip(1000.0f);
    camera.setDistance(camDistance);

    gui.setPosition(viewOriginX+viewHalfWidth*0.4f, 0);
}

///--------------------------------------------------------------
void S3BaseObj::update()
{
    camera.setDistance(camDistance);
}

///--------------------------------------------------------------
void S3BaseObj::draw()
{
#ifdef OF_DEBUG
    if (SettingsManager::getInstance().debugShowGUI)
    {
        gui.draw();
    }

    ofSetColor(ofColor::gray);
    ofxBitmapString(viewOriginX, viewHalfHeight) << cursorIds.size();
#endif
}

///--------------------------------------------------------------
void S3BaseObj::drawLoop()
{
    ofSetLineWidth(2);

    // Draw loop arc
    loopArc.clear();
    int convertedAngle = ANGLE_OFFSET + 360-loopAngle;
    int angleStart =  convertedAngle - 30;
    int angleEnd = convertedAngle;
    loopArc.arc(objPosition, loopRadius, loopRadius, angleStart, angleEnd, LOOP_RESOLUTION);
    loopArc.draw();

    // Draw axis
    // Top
    ofPushMatrix();
    ofTranslate(objPosition.x, objPosition.y); // Move to center of object
    ofRotateZ(360-loopAngle); // Rotate line according to the angle
    ofTranslate(0, loopRadius); // Move it so that it starts at the arc perimeter
    ofLine(0, 0, 0, AXIS_LENGTH);
    ofPopMatrix();
    // Bottom
    ofPushMatrix();
    ofTranslate(objPosition.x, objPosition.y); // Move to center of object
    ofRotateZ(360-loopAngle); // Rotate line according to the angle
    ofTranslate(0, -loopRadius); // Move it so that it starts at the arc perimeter
    ofLine(0, 0, 0, -AXIS_LENGTH);
    ofPopMatrix();
}

void S3BaseObj::drawWhiteCircle()
{
    ofDisableLighting();
    ofSetColor(ofColor::white);
    ofCircle(objPosition.x, objPosition.y, 0, whiteCircleRadius);
}

void S3BaseObj::drawPinchCircle()
{
    ofDisableLighting();
    ofSetColor(255, 2255, 255, pinchImageAlpha);
    pinchImage.draw(objPosition, pinchImageSize, pinchImageSize);

}

///--------------------------------------------------------------
void S3BaseObj::windowResized(ofResizeEventArgs &args)
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
bool S3BaseObj::pick(int screenX, int screenY)
{
    ofVec3f centerScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    ofVec3f perimeterScreenCoords = camera.worldToScreen(ofVec3f(objPosition.x, objPosition.y - radius, objPosition.z), viewRectangle);

    float distToPerimeter = ofDistSquared(centerScreenCoords.x, centerScreenCoords.y, perimeterScreenCoords.x, perimeterScreenCoords.y);
    float distToScreen = ofDistSquared(centerScreenCoords.x, centerScreenCoords.y, screenX, screenY);

    isPicked = distToScreen <= distToPerimeter;

    return isPicked;
}

///--------------------------------------------------------------
void S3BaseObj::unpick()
{
    isPicked = false;
}

///--------------------------------------------------------------
bool S3BaseObj::getIsPicked()
{
    return isPicked;
}

///--------------------------------------------------------------
void S3BaseObj::enablePinch(bool enable)
{
    pinchEnabled = enable;

    if (!pinchEnabled) return;

    if (cursorIds.size() <= 1)
    {
        pinchEnabled = false;
        return;
    }

    int cursorId1 = cursorIds.front();
    int cursorId2 = cursorIds.back();

    pinchInitialDist = TUIOHandler::getInstance().getDistBetweenCursors(cursorId1, cursorId2);

    pinchImageSize = whiteCircleRadius / 2;
}

///--------------------------------------------------------------
bool S3BaseObj::isPinchEnabled()
{
    return pinchEnabled;
}

///--------------------------------------------------------------
void S3BaseObj::updatePinch()
{
    if (!pinchEnabled) return;

    int cursorId1 = cursorIds.front();
    int cursorId2 = cursorIds.back();
    float pinchCurrentDist = TUIOHandler::getInstance().getDistBetweenCursors(cursorId1, cursorId2);

    float diff = pinchCurrentDist - pinchInitialDist;
    if (diff > 0)
    {
        pinchImageSize = whiteCircleRadius + diff/4;
        pinchImageAlpha = int(ofMap(pinchCurrentDist, pinchInitialDist, pinchInitialDist*2.0f, pinchImageAlphaMin, pinchImageAlphaMax, true));
    }
}

///--------------------------------------------------------------
int S3BaseObj::getFirstCursorId()
{
    if (cursorIds.empty()) return -1;
    return cursorIds.front();
}

///--------------------------------------------------------------
void S3BaseObj::setPositionFromScreenCoords(int screenX, int screenY)
{
    ofVec3f objScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    objScreenCoords.y = screenY;

    float oldX = objPosition.x;

    objPosition = camera.screenToWorld(objScreenCoords, viewRectangle);
    objPosition.x = oldX;
}

///--------------------------------------------------------------
void S3BaseObj::setAnimated(bool animate)
{
    isAnimated = animate;
}

#pragma mark - TUIO

void S3BaseObj::addCursor(int cursorId)
{
    cursorIds.push_back(cursorId);
}

void S3BaseObj::removeLastCursor()
{
    if (cursorIds.empty()) return;
    cursorIds.pop_back();
}