//
//  S2DrumsAmoebaCPU.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S2DrumsAmoebaCPU.h"
#include "SettingsManager.h"

///--------------------------------------------------------------
S2DrumsAmoebaCPU::S2DrumsAmoebaCPU(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::loadSettings()
{
    if (settingsPath.empty()) return;
    S2BaseObj::initSharedSettings();

    // Custom object settings go here
    gui.add(tempo.set("tempo", 1, 0,8));

    // perlin noise
    gui.add(noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 200.0 ) );
    gui.add(doThreshold.set( "Threshold", false ) );
    gui.add(thresholdLow.set( "Treshold Low", 0, 0, 255 ) );
    gui.add(thresholdHigh.set( "Treshold High", 128, 0, 255 ) );
    gui.add(showNormals.set( "show normals", false ) );
    gui.add(offset.set("offset",100.0,-200.0f,200.0f));
    
    gui.loadFromFile(settingsPath);
    
    //cout << "Amoeba : stable noise freq. on load : " << noiseFrequency << endl;

}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::setup()
{
    S2BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(3);

    camera.setTarget(sphere);
    
    bool enableVBO;
#ifdef OF_DEBUG
    enableVBO = SettingsManager::getInstance().debugEnableVBO;
#else
    enableVBO = SettingsManager::getInstance().releaseEnableVBO;
#endif
    sphere.setUseVbo(enableVBO);


    // shader

    if (!shader.isLoaded())
        shader.load("objects/drums_amoeba/shaders/shader");
    ofDisableArbTex();

    /// CREATE NOISE IMAGE
    if (isFirstSetup)
    {
        noisePixels.allocate(100, 100, 1);
        noiseImage.allocate(100, 100, OF_IMAGE_GRAYSCALE);

        for(int i=0;i<100;i++)
            for(int j=0;j<100;j++)
                noisePixels[((j*100)+i)*1] = 255;

        noiseImage.setFromPixels(noisePixels);
        
        vertexNormals = sphere.getMesh().getNormals();
        vertexOriginals = sphere.getMesh().getVertices();
        uvOriginals = sphere.getMesh().getTexCoords();

    }

    
    
    isFirstSetup = false;
    
    // Max offset is the minimum offset applied with volume reaction
    // stable offset is the inactive state one ... it copys from offset at startup (load xml)
    maxOffset = 38;
    stableOffset = 18;

    
    Tweenzor::resetAllTweens();

}


///--------------------------------------------------------------
void S2DrumsAmoebaCPU::initInactive()
{
    
    colorImageAlpha = 0;
    
    //cout << "INIT INACTIVE " << endl;
    inactiveNoiseFrequency = 18;
    inactiveCircleRadius = 0;
    inactiveCircleAlpha = 0;

    transitionCircleRadius = 0;
    transitionCircleAlpha = 255;
    activeNoiseFrequency = 30;

    maxVolumeCircleRadius = 50;
    maxVolumeCircleAlpha = 250;
    

    // noise set to original position
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,inactiveNoiseFrequency, 0, 0.3, EASE_IN_OUT_SINE);

    // white circle set to original position
    Tweenzor::add(&volumeCircleRadius, volumeCircleRadius, inactiveCircleRadius, 0, 0.6, EASE_IN_OUT_SINE);
    Tweenzor::add(&volumeCircleAlpha, volumeCircleAlpha,  inactiveCircleAlpha,  0, 0.6, EASE_IN_OUT_SINE);

}
///--------------------------------------------------------------
void S2DrumsAmoebaCPU::updateInactive()
{
    //cout << "Update INACTIVE " << endl;
    updateActive(); // Delete this line if it needs a custom update
    if(shouldChangeState)
    {
        //cout << " CHANGE FROM INACTIVE TO NEXT TRANSITION" << endl;
        changeState();
    }
}


///--------------------------------------------------------------
void S2DrumsAmoebaCPU::initTransitioning()
{
    //cout << "INIT TRANSITION" << endl;
    float delay = 0.0f;
    float duration = 0.4f;

    // noise frequency
    Tweenzor::add((float*)&noiseFrequency.get(), inactiveNoiseFrequency, activeNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&noiseFrequency.get()), this, &S2DrumsAmoebaCPU::onCompleteTransitioning);

    // white circle
    Tweenzor::add(&transitionCircleRadius, 0, maxVolumeCircleRadius, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitionCircleAlpha, maxVolumeCircleAlpha, 0.0f, delay, duration, EASE_IN_OUT_SINE);

}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::updateTransitioning()
{
    //cout << "UPDATE TRANSITION" << endl;
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::onCompleteTransitioning(float* arg)
{

    float delay = 0.0f;
    float duration = 0.4f;
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,inactiveNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&noiseFrequency.get()), this, &S2DrumsAmoebaCPU::onCompleteTransitioningToActive);

    ////cout << "on COMPLETE TRANSITION ... so NEW TWWEEN TO ACTIVE COÑO!!" << endl;
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::onCompleteTransitioningToActive(float* arg)
{
    nextState = S3ObjStateActive;
    shouldChangeState = true;
    changeState();
    
    transitionCircleRadius = 0;
    transitionCircleAlpha = 255;
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::updateActive()
{
    Tweenzor::update(int(ofGetElapsedTimeMillis()));

    inactiveNoiseFrequency = inactiveNoiseFrequency;
    
    
    
    // perlin noise time
    float time = ofGetElapsedTimef();

    /// RECREATE NOISE IMAGE
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<50;j++)
        {
            noisePixels[((i*100)+j)*1] = 255.0 * ofNoise(i / noiseFrequency,j/noiseFrequency,time/tempo );
            noisePixels[((i*100)+99-j)*1] = 255.0 * ofNoise(i / noiseFrequency,j/noiseFrequency,time/tempo );

            if(doThreshold)
            {
                if((noisePixels[((i*100)+j)*1]>=thresholdLow)&&(noisePixels[((i*100)+j)*1]<=thresholdHigh))
                {
                    noisePixels[((i*100)+j)*1] = 255;
                    noisePixels[((i*100)+99-j)*1] = 255;
                }
                else
                {
                    noisePixels[((i*100)+j)*1] = 0;
                    noisePixels[((i*100)+99-j)*1] = 0;
                }
            }

        }
    }
    noiseImage.setFromPixels(noisePixels);
    
    /// UPDATE VERTEXS BASED ON NOISE IMAGE
    for(int i=0;i<vertexOriginals.size();i++)
    {
        int ii,jj;
        
        ii = ofMap(uvOriginals[i].x,0.0,1.0,0.0,99.0);
        jj = ofMap(uvOriginals[i].y,0.0,1.0,0.0,99.0);
        
        float noiseValue = float(noisePixels[(ii*100)+ jj])/255.0;
        vertexOffset = offset * noiseValue;
        
        //cout << uvOriginals[i] << " :: " << ii << " , " << jj << endl;
        
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
void S2DrumsAmoebaCPU::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::drawActive()
{
    camera.begin(viewRectangle);
    {
        glPointSize(2.0);

        ofSetColor(ofColor::white);
        
        sphere.drawVertices();

        if(showNormals)
        {
            // draw normals
            ofSetColor(255,0,0,255);
            sphere.drawNormals(3);
        }
        
        
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
            // Circle
            ofFill();
            ofSetColor(255, 255, 255, volumeCircleAlpha);
            ofCircle(objPosition.x, objPosition.y, 0, volumeCircleRadius);
        }

        ofDisableDepthTest();

        drawPinchCircle();
        drawPinchColor();
        drawWhiteCircle();
        drawLoop();
        
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
//
//        ofCircle(0,0,200);

    }
    camera.end();
    
    //noiseImage.draw(0,0);
}

///--------------------------------------------------------------
void S2DrumsAmoebaCPU::volumeChanged(float &newVolume)
{
    
    float toRadius = ofMap(newVolume,0.0,1.0,0, maxVolumeCircleRadius);
    float toAlpha = ofMap(newVolume,0.0,1.0,0, maxVolumeCircleAlpha);
    float toFrequency = ofMap(newVolume,0.0,1.0,40,1);
    float toOffset = ofMap(newVolume,0.0,1.0,stableOffset,maxOffset);
    // white circle
//    Tweenzor::add(&volumeCircleRadius, volumeCircleRadius, toRadius, 0, 0.1, EASE_IN_OUT_SINE);
//    Tweenzor::add(&volumeCircleAlpha, volumeCircleAlpha, toAlpha, 0, 0.1, EASE_IN_OUT_SINE);
//    Tweenzor::add((float*)&noiseFrequency.get(), noiseFrequency, toFrequency, 0, 0.1, EASE_IN_OUT_SINE);

    volumeCircleRadius = toRadius;
    volumeCircleAlpha = toAlpha;
    //noiseFrequency = toFrequency;
    //offset=toOffset;
}


///--------------------------------------------------------------
void S2DrumsAmoebaCPU::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}
