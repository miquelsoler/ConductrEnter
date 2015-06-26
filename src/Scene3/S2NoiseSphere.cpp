//
//  S2NoiseSphere.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S2NoiseSphere.h"

///--------------------------------------------------------------
S2NoiseSphere::S2NoiseSphere(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2NoiseSphere::loadSettings()
{
    if (settingsPath.empty()) return;
    S2BaseObj::initSharedSettings();

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
void S2NoiseSphere::setup()
{
    S2BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(32);

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

    if (isFirstSetup)
    {
        sphereFacesOriginal = sphere.getMesh().getUniqueFaces();
        sphereFacesCurrent = sphere.getMesh().getUniqueFaces();

        vertexOffset = 140;
        vertexNormals = sphere.getMesh().getNormals();
        vertexOriginals = sphere.getMesh().getVertices();
    }

    isFirstSetup = false;

    Tweenzor::resetAllTweens();

}

///--------------------------------------------------------------
void S2NoiseSphere::initInactive()
{
    stableOffset = 6;
    stableNoiseFrequency = 50;
    activeOffset = 25;
    activeNoiseFrequency = 1000;
 
    float delay = 0.0f;
    float duration = 0.8f;
    
    // noise frequency reset
    Tweenzor::add((float*)&noiseFrequency.get(), noiseFrequency, stableNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    // offset reset
    Tweenzor::add((float*)&offset.get(), offset, stableOffset, delay, duration, EASE_IN_OUT_SINE);

    
}

///--------------------------------------------------------------
void S2NoiseSphere::updateInactive()
{
    
//    cout << "UPDATE INACTIVE " << endl;
    
    updateActive(); // Delete this line if it needs a custom update
    
    if(shouldChangeState)
    {
//        cout << "from INactive Changed State !!! " << endl;
        changeState();
        
    }
}

///--------------------------------------------------------------
void S2NoiseSphere::initTransitioning()
{
//    cout << "INIT TRANSITION" << endl;
    
    float delay = 0.0f;
    float duration = 0.3f;
    
    // noise frequency
    Tweenzor::add((float*)&offset.get(), stableOffset, activeOffset, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&offset.get()), this, &S2NoiseSphere::onCompleteTransitioning);
    
}


///--------------------------------------------------------------
void S2NoiseSphere::updateTransitioning()
{
//    cout << "UPDATE TRANSITIONING " << endl;
    
    updateActive(); // Delete this line if it needs a custom update
    
    if(shouldChangeState)
    {
//        cout << "from TRANSITIONING Changed State !!! " << endl;
        changeState();
    }

}

///--------------------------------------------------------------
void S2NoiseSphere::onCompleteTransitioning(float* arg)
{
//    cout << " ON COMPLETE TRANSITIONING" << endl;
    
    float delay = 0.0f;
    float duration = 0.3f;
    
    Tweenzor::add((float*)&offset.get(),offset ,stableOffset, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&offset.get()), this, &S2NoiseSphere::onCompleteToActive);

    
}

///--------------------------------------------------------------
void S2NoiseSphere::onCompleteToActive(float* arg)
{
    float delay = 0.0f;
    float duration = 0.2f;
    
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,activeNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);

//    cout << "ON COMPLETE TO ACTIVE" << endl;
    nextState = S3ObjStateActive;
    shouldChangeState = true;
    
}

///--------------------------------------------------------------
void S2NoiseSphere::initActive()
{
//    cout << " INIT ACTIVE !!!! " << endl;
    
}


///--------------------------------------------------------------
void S2NoiseSphere::updateActive()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    
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
//            //            trianglesCurrent[i].setVertex(j, trianglesOriginal[i].getVertex(j) - (vertexDistance*noises[i])*triangleNormal);
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
void S2NoiseSphere::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2NoiseSphere::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2NoiseSphere::drawActive()
{

    camera.begin();
    {
        ofSetCircleResolution(64);
        glPointSize(2.0);
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
        
//        ofColor particleColor;
//        
//        switch(currentState)
//        {
//            case S3ObjStateInactive:        particleColor = ofColor::red; break;
//            case S3ObjStateTransitioning:   particleColor = ofColor::orange; break;
//            case S3ObjStateActive :         particleColor = ofColor::green; break;
//                
//            default:                        break;
//        }
//        ofSetColor(particleColor);

        
        sphere.setScale(1.01f);
        sphere.drawVertices();
        sphere.setScale(1.f);

/*
        ofDisableDepthTest();
        //------------------//
*/


        drawWhiteCircle();
        
        ofSetColor(255);
        if (pinchEnabled) drawPinchCircle();
        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S2NoiseSphere::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}

///--------------------------------------------------------------
void S2NoiseSphere::volumeChanged(float &newVolume)
{
    float newOffset = ofMap(newVolume,0.0,1.0,stableOffset,40.0);
    Tweenzor::add((float*)&offset.get(),offset ,newOffset, 0, 0.1, EASE_IN_OUT_SINE);
}
