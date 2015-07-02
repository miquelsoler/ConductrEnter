//
//  S2NoiseSphere.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S2NoiseSphere.h"

#include "SettingsManager.h"

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
    sphereAudio.setRadius(radius);
    sphereAudio.setPosition(objPosition);
    sphereAudio.setResolution(32);
    
    bool enableVBO;
#ifdef OF_DEBUG
    enableVBO = SettingsManager::getInstance().debugEnableVBO;
#else
    enableVBO = SettingsManager::getInstance().releaseEnableVBO;
#endif
    sphere.setUseVbo(enableVBO);
    sphereAudio.setUseVbo(enableVBO);

    camera.setTarget(sphere);
    
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
    stableOffset = 0;
    stableNoiseFrequency = 50;
    activeOffset = 1;
    activeNoiseFrequency = 100;
 
    inactiveCircleRadius = 0;
    inactiveCircleAlpha = 0;
    transitionCircleRadius = 0;
    transitionCircleAlpha = 255;
    maxCircleRadius = 50;
    maxCircleAlpha = 250;

    
    
    float delay = 0.0f;
    float duration = 0.8f;
    
    // noise frequency reset
    Tweenzor::add((float*)&noiseFrequency.get(), noiseFrequency, stableNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    // offset reset
    Tweenzor::add((float*)&offset.get(), offset, stableOffset, delay, duration, EASE_IN_OUT_SINE);

    // white circle set to original position
    Tweenzor::add(&activeCircleRadius, activeCircleRadius, inactiveCircleRadius, 0, 0.6, EASE_IN_OUT_SINE);
    Tweenzor::add(&activeCircleAlpha , activeCircleAlpha,  inactiveCircleAlpha,  0, 0.6, EASE_IN_OUT_SINE);

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
    
    // white circle
    Tweenzor::add(&transitionCircleRadius, 0, maxCircleRadius, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitionCircleAlpha, maxCircleAlpha, 0.0f, delay, duration, EASE_IN_OUT_SINE);

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

//    cout << "ON COMPLETE TRANSITION SO TO ACTIVE" << endl;
    nextState = S3ObjStateActive;
    shouldChangeState = true;
    
    transitionCircleRadius = 0;
    transitionCircleAlpha = 255;

}

///--------------------------------------------------------------
void S2NoiseSphere::initActive()
{
}


///--------------------------------------------------------------
void S2NoiseSphere::updateActive()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));
    
    //sphere.rotate(0.3, 0.0, 1.0, 0.0);

    // perlin noise
    float time = ofGetElapsedTimef();

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

    camera.begin(viewRectangle);
    {
        ofSetCircleResolution(64);
        glPointSize(1.0);

        // sphere
        ofSetColor(ofColor::white);
        
//        ofColor c;
//        switch(currentState)
//        {
//            case S3ObjStateInactive:
//                c = ofColor(255,0,0);
//                break;
//            case S3ObjStateTransitioning:
//                c = ofColor(255,128,0);
//                break;
//            case S3ObjStateActive:
//                c = ofColor(0,255,0);
//                break;
//        }
//        ofSetColor(c);
        
        sphere.setScale(1.01f);
        sphere.drawVertices();
        sphere.setScale(1.f);

        // Draw transitioning circle
        if (currentState == S3ObjStateTransitioning)
        {
            // Circle
            ofFill();
            ofSetColor(255, 255, 255, transitionCircleAlpha);
            ofCircle(objPosition.x, objPosition.y, 0, transitionCircleRadius);
        }
        else if (currentState == S3ObjStateActive)
        {
            // Draw Audio Sphere
            ofFill();
            ofSetColor(255, 255, 255, activeCircleAlpha);
            //ofCircle(objPosition.x, objPosition.y, 0, volumeCircleRadius);
            sphereAudio.setRadius(activeCircleRadius);
            ofSetColor(255*activeCircleAlpha/maxCircleRadius, 255*activeCircleAlpha/maxCircleRadius, 255*activeCircleAlpha/maxCircleRadius, activeCircleAlpha);
            sphereAudio.drawVertices();
            sphereAudio.setScale(1.0);
        }

        
        
        drawPinchCircle();
        drawPinchColor();
        drawWhiteCircle();
        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S2NoiseSphere::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
    sphereAudio.setPosition(objPosition);
}

///--------------------------------------------------------------
void S2NoiseSphere::volumeChanged(float &newVolume)
{
    float newOffset = ofMap(newVolume,0.0,1.0,stableOffset,1.0);
    float toRadius = ofMap(newVolume,0.0,1.0,0,maxCircleRadius);
    float toAlpha = ofMap(newVolume,0.0,1.0,0,maxCircleAlpha);

    activeCircleRadius = toRadius;
    activeCircleAlpha = toAlpha;
    //Tweenzor::add((float*)&offset.get(),offset ,newOffset, 0, 0.1, EASE_IN_OUT_SINE);
    offset = newOffset;
}
