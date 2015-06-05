//
//  S3BaseObj.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3BaseObj.h"
#include "ofxAppUtils.h"

const int LOOP_RESOLUTION = 50;
const int ANGLE_OFFSET = 90;
const int AXIS_LENGTH = 6;

#pragma mark - Initialization

S3BaseObj::S3BaseObj(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath)  : BaseObject(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    camera.disableMouseInput();

    settingsPath = _settingsPath;
//    loadSettings(); // NURIA

#ifdef OF_DEBUG
    drawGui = true;
#endif
}

void S3BaseObj::setAnimated(bool animate)
{
    isAnimated = animate;
}

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
