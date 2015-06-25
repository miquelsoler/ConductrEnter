//
//  Scene1ArtistZone.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 25/6/15.
//
//

#include "Scene1ArtistZone.h"

#include "ofMain.h"

const float ARTISTZONE_X_MARGIN = 0.010416667;
const float ARTISTZONE_Y_MARGIN = 0.037037037;

///--------------------------------------------------------------
Scene1ArtistZone::Scene1ArtistZone(float _originX, float _originY, float _width, float _height)
{
    originX = _originX;
    originY = _originY;
    width = _width;
    height = _height;
}

///--------------------------------------------------------------
void Scene1ArtistZone::draw()
{
    float xIni, yIni;
    float xEnd, yEnd;
    float w, h;

    xIni = (originX - ARTISTZONE_X_MARGIN) * ofGetWidth();
    yIni = (originY - (height/2.0f) - ARTISTZONE_Y_MARGIN) * ofGetHeight();
    xEnd = (originX + width + (ARTISTZONE_X_MARGIN * 2)) * ofGetWidth();
    yEnd = (originY + (height/2.0f) + ARTISTZONE_Y_MARGIN) * ofGetHeight();
    w = xEnd - xIni;
    h = yEnd - yIni;

    ofFill();
    ofSetColor(50, 100, 100, 50);
    ofRect(xIni, yIni, w, h);
    ofNoFill();
    ofSetColor(50, 100, 100, 255);
    ofRect(xIni, yIni, w, h);
}

///--------------------------------------------------------------
bool Scene1ArtistZone::isCoordinateInside(float percentX, float percentY)
{
    bool result;

    float xIni, yIni;
    float xEnd, yEnd;
    float w, h;

    xIni = originX - ARTISTZONE_X_MARGIN;
    yIni = originY - (height/2.0f) - ARTISTZONE_Y_MARGIN;
    xEnd = originX + width + (ARTISTZONE_X_MARGIN * 2);
    yEnd = originY + (height/2.0f) + ARTISTZONE_Y_MARGIN;

    result = (percentX >= xIni) && (percentX <=xEnd) && (percentY >= yIni) && (percentY <= yEnd);

    return result;
}
