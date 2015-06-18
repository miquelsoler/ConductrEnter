//
//  S3NoiseSphere.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3NoiseSphere.h"

///--------------------------------------------------------------
S3NoiseSphere::S3NoiseSphere(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3NoiseSphere::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here

    gui.add(tempo.set("tempo", 1, 0,8));

    // perlin noise
    gui.add( noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 4096.0f ) );
    gui.add( offset.set( "offset",0,-200,200) );
    gui.add( mode.set( "mode",0,0,2) );

    gui.add( doThreshold.set( "Threshold", false ) );
    gui.add( thresholdLow.set( "Treshold Low", 0, 0, 40 ) );
    gui.add( thresholdHigh.set( "Treshold High", 40, 0, 40 ) );

    gui.loadFromFile(settingsPath);
}

///--------------------------------------------------------------
void S3NoiseSphere::setup()
{
    S3BaseObj::setup();

    ofSetSmoothLighting(true);
    ofSetVerticalSync(true);
    ofSetCircleResolution(64);
    glPointSize(2.0);

    // color image: candidat a codi comœ
    imgColorsCircle.loadImage("objects/color_circle.png");

    sphere.setRadius(radius);
    sphere.setResolution(32);
    sphere.setPosition(objPosition);
    camera.setTarget(sphere);

/*
    // lights
    pointLight1.setDiffuseColor( ofFloatColor(0, 1.0, 160.0/255.0) );
    pointLight1.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    pointLight2.setDiffuseColor( ofFloatColor( 247.0/255.f, 66.f/255.f, 55.0/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(1.0f, 1.0f, 1.0f));

    pointLight3.setDiffuseColor( ofFloatColor(68.0/255.f,187.0/255.f,209.0/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(1.0,1.0,1.0) );

    // lights positions
    pointLight1.setPosition(ofGetWidth()/4 ,ofGetHeight()/4,200);
    pointLight2.setPosition((ofGetWidth()/4)*3 ,ofGetHeight()/2,200);
    pointLight3.setPosition(ofGetWidth()/4,(ofGetHeight()/4)*3,200);
*/

    sphereFacesOriginal = sphere.getMesh().getUniqueFaces();
    sphereFacesCurrent = sphere.getMesh().getUniqueFaces();

    vertexOffset = 140;
    vertexNormals = sphere.getMesh().getNormals();
    vertexOriginals = sphere.getMesh().getVertices();

    noiseStartX = 0;
    noiseStartY = 0;
}

///--------------------------------------------------------------
void S3NoiseSphere::update()
{
    S3BaseObj::update();

    sphere.rotate(0.3, 0.0, 1.0, 0.0);
    // set sphere radius on sinus
/*
    if(isTouchDown) sphere.setRadius(fabs(sin(ofGetElapsedTimef()*3)*80)+150);
    else sphere.setRadius(150);
    sphere.setRadius(radiusTween + fabs(sin(ofGetElapsedTimef()*3)*80) );
*/

    // perlin noise
    float time = ofGetElapsedTimef();


/// trying to change color for each vertex ...
//    vector<ofFloatColor> sphereVertexColors = sphere.getMesh().getColors();
//    for(int i = 0 ; i< sphereVertexColors.size();i++)
//    {
//        sphere.getMesh().setColor(i,ofFloatColor(ofRandomf(),ofRandomf(),ofRandomf()));
//    }

//    ofVec3f triangleNormal;
//    int size = (int)sphereFacesOriginal.size();
//
//    for (int i=0; i<size; i=i+1) {
//
//        for (int j=0; j<3; j++) {
//            //            trianglesCurrent1[i].setVertex(j, trianglesOriginal1[i].getVertex(j) - (vertexDistance*noises1[i])*triangleNormal);
//
//            vertexOffset = 10 * ofSignedNoise(i,i+j,ofGetElapsedTimef());
//
//            ofVec3f newVertex =sphereFacesOriginal[i].getVertex(j);
//
//            sphereFacesCurrent[i].setVertex(j, sphereFacesOriginal[i].getVertex(j) - vertexOffset*triangleNormal);
//        }
//    }
//    sphere.getMesh().setFromTriangles(sphereFacesCurrent);

    for(int i=0;i<vertexOriginals.size();i++)
    {
        switch (mode)
        {
            case 0 :
                vertexOffset = offset * ofSignedNoise(i/noiseFrequency,time/tempo);
                break;
            case 1 :
                vertexOffset = offset * ofNoise(i / noiseFrequency,vertexOriginals.size()-i / noiseFrequency,time/tempo );
                break;
            case 2 :
                vertexOffset = offset * ofNoise(i / noiseFrequency ,i+1/ noiseFrequency,time/tempo );
                break;
        }
        
        
        if(doThreshold)
        {
            if((vertexOffset>=thresholdLow)&&(vertexOffset<=thresholdHigh))
            {
                vertexOffset = vertexOffset;
            }
            else
            {
                vertexOffset=0;
            }
        }
        
        ofVec3f newPos = vertexOriginals[i] + vertexOffset * vertexNormals[i];
        sphere.getMesh().setVertex(i, newPos);
    }
    

/*
    // update light colors
    pointLight1.setDiffuseColor( ofFloatColor(    ofMap(mouseInteractionX,0.0,1.0,1.0,0.0),     ofMap(mouseInteractionX,0.0,1.0,1.0,1.0),     ofMap(mouseInteractionX,0.0,1.0,1.0,160.0/255.0)) );
    pointLight2.setDiffuseColor( ofFloatColor(  ofMap(mouseInteractionX,0.0,1.0,1.0,247.0/255.f), ofMap(mouseInteractionX,0.0,1.0,1.0,66.f/255.f), ofMap(mouseInteractionX,0.0,1.0,1.0,55.0/255.f) ));
    pointLight3.setDiffuseColor( ofFloatColor(ofMap(mouseInteractionX,0.0,1.0,1.0,68.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,187.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,209.0/255.f)) );
*/
}

///--------------------------------------------------------------
void S3NoiseSphere::draw()
{
    S3BaseObj::draw();

    camera.begin(viewRectangle);
    {
        //------------------//
/*
        ofEnableDepthTest();
        ofEnableLighting();
*/

/*
        pointLight1.enable();
        pointLight2.enable();
        pointLight3.enable();
*/

        // sphere
        ofSetColor(ofColor::white);
        sphere.setScale(1.01f);
        sphere.drawVertices();
        sphere.setScale(1.f);

/*
        ofDisableDepthTest();
        //------------------//
*/

/*
        // color image
        ofSetColor(ofFloatColor(1.0,1.0,1.0,ofMap(mouseInteractionX,0.0,1.0,0.0,0.55)));
        imgColorsCircle.setAnchorPercent(0.5,0.5);
*/

/*
        float circleSize = ofMap(mouseInteractionX,0.0,1.0,60.0,200);
        imgColorsCircle.draw(ofGetWidth()/2,ofGetHeight()/2,circleSize,circleSize);
*/

        // white circle
//        ofDisableLighting();
        ofSetColor(255);
        ofCircle(ofGetWidth()/2,ofGetHeight()/2,40);

        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S3NoiseSphere::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}
