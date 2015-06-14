//
//  S3BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S3BaseObj.h"

const int LOOP_RESOLUTION = 50;
const int ANGLE_OFFSET = 90;
const int AXIS_LENGTH = 6;

#pragma mark - Initialization

///--------------------------------------------------------------
S3BaseObj::S3BaseObj(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath)  : BaseObject(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    camera.disableMouseInput();

    settingsPath = _settingsPath;
}

///--------------------------------------------------------------
void S3BaseObj::initSharedSettings()
{
    gui.setup("Settings", settingsPath);
    gui.add(camDistance.set("Camera_Distance", 0, 0, 500));
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
    camera.setFarClip(500.0f);
    camera.setDistance(camDistance);

//    printf("Obj: (%f,%f,%f) - Cam: (%f,%f,%f)\n", objPosition.x, objPosition.y, objPosition.z, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

    gui.setPosition(viewOriginX, 0);
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
    gui.draw();
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

///--------------------------------------------------------------
void S3BaseObj::windowResized(ofResizeEventArgs &args)
{
    viewWidth = args.width / sceneNumObjects;
    viewHalfWidth = viewWidth / 2.0f;
    viewHalfHeight = args.height / 2.0f;
    viewOriginX = sceneObjectIndex * viewWidth;
    objPosition.x = viewOriginX + viewHalfWidth;
    objPosition.y = viewHalfHeight;
    viewRectangle = ofRectangle(viewOriginX, 0, viewWidth, args.height);

    gui.setPosition(viewOriginX, 0);

    camera.setDistance(camDistance);
}

///--------------------------------------------------------------
bool S3BaseObj::pick(int screenX, int screenY)
{
    ofVec3f centerScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    ofVec3f topScreenCoords = camera.worldToScreen(ofVec3f(objPosition.x, objPosition.y - radius, objPosition.z), viewRectangle);

    float distToTop = ofDistSquared(centerScreenCoords.x, centerScreenCoords.y, topScreenCoords.x, topScreenCoords.y);
    float distToScreen = ofDistSquared(centerScreenCoords.x, centerScreenCoords.y, screenX, screenY);

    isPicked = distToScreen <= distToTop;

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
void S3BaseObj::setPositionFromScreenCoords(int screenX, int screenY)
{
    ofVec3f objScreenCoords = camera.worldToScreen(objPosition, viewRectangle);
    objScreenCoords.y = screenY;

    objPosition = camera.screenToWorld(objScreenCoords, viewRectangle);
}

///--------------------------------------------------------------
void S3BaseObj::setAnimated(bool animate)
{
    isAnimated = animate;
}
