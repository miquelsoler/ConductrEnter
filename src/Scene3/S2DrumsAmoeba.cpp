//
//  S2DrumsAmoeba.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S2DrumsAmoeba.h"

///--------------------------------------------------------------
S2DrumsAmoeba::S2DrumsAmoeba(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2DrumsAmoeba::loadSettings()
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
    gui.add(offset.set("offset",100.0,-200.0,200.0));
    
    gui.loadFromFile(settingsPath);
    
    stableNoiseFrequency = noiseFrequency;
    cout << "Amoeba : stable noise freq. on load : " << noiseFrequency << endl;

}

///--------------------------------------------------------------
void S2DrumsAmoeba::setup()
{
    S2BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    camera.setTarget(sphere);


    // lights
    pointLight1.setDiffuseColor( ofFloatColor(0, 1.0, 160.0/255.0) );
    pointLight1.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    pointLight2.setDiffuseColor( ofFloatColor( 247.0/255.f, 66.f/255.f, 55.0/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(1.0f, 1.0f, 1.0f));

    pointLight3.setDiffuseColor( ofFloatColor(68.0/255.f,187.0/255.f,209.0/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(1.0,1.0,1.0) );

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
    }

    isFirstSetup = false;
    Tweenzor::resetAllTweens();

}


///--------------------------------------------------------------
void S2DrumsAmoeba::initInactive()
{
    activeNoiseFrequency = 20;
    
    stableCircleRadius = 0;
    stableCircleAlpha = 0;

    activeCircleAlpha = 250;
    activeCircleRadius = whiteCircleRadius*3;

    // noise set to original position
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,stableNoiseFrequency, 0, 0.3, EASE_IN_OUT_SINE);

    // white circle set to original position
    Tweenzor::add(&volumeCircleRadius, volumeCircleRadius, stableCircleRadius, 0, 0.6, EASE_IN_OUT_SINE);
    Tweenzor::add(&volumeCircleAlpha , volumeCircleAlpha,  stableCircleAlpha,  0, 0.6, EASE_IN_OUT_SINE);

}
///--------------------------------------------------------------
void S2DrumsAmoeba::updateInactive()
{
    updateActive(); // Delete this line if it needs a custom update
    
    if(shouldChangeState)
    {
        //cout << " CHANGE FROM INACTIVE TO NEXT TRANSITION" << endl;
        changeState();
    }
}


///--------------------------------------------------------------
void S2DrumsAmoeba::initTransitioning()
{
    float delay = 0.0f;
    float duration = 0.4f;

    // noise frequency
    Tweenzor::add((float*)&noiseFrequency.get(), stableNoiseFrequency, activeNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&noiseFrequency.get()), this, &S2DrumsAmoeba::onCompleteTransitioning);

    // white circle
    Tweenzor::add(&volumeCircleRadius, whiteCircleRadius, activeCircleRadius, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&volumeCircleAlpha, activeCircleAlpha, 0.0f, delay, duration, EASE_IN_OUT_SINE);

}

///--------------------------------------------------------------
void S2DrumsAmoeba::updateTransitioning()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S2DrumsAmoeba::onCompleteTransitioning(float* arg)
{
    float delay = 0.0f;
    float duration = 0.4f;
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,stableNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    
    if(shouldChangeState)
    {
        //        cout << " CHANGE FROM TRANSITION TO NEXT ACTIVE" << endl;
        changeState();
    }
}

///--------------------------------------------------------------
void S2DrumsAmoeba::updateActive()
{
    // lights positions
    pointLight1.setPosition(radius*2,-radius*1.5,400);
    pointLight2.setPosition(radius*2 ,radius*1.5,400);
    pointLight3.setPosition(-radius*2,0,400);

//    sphere.rotate(0.3, 0.0, 1.0, 0.0);

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


    /*
     // update light colors
     pointLight1.setDiffuseColor( ofFloatColor(ofMap(mouseInteractionX,0.0,1.0,1.0,0.0),ofMap(mouseInteractionX,0.0,1.0,1.0,1.0),ofMap(mouseInteractionX,0.0,1.0,1.0,160.0/255.0)) );
     pointLight2.setDiffuseColor( ofFloatColor(ofMap(mouseInteractionX,0.0,1.0,1.0,247.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,66.f/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,55.0/255.f) ));
     pointLight3.setDiffuseColor( ofFloatColor(ofMap(mouseInteractionX,0.0,1.0,1.0,68.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,187.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,209.0/255.f)) );
     */
}

///--------------------------------------------------------------
void S2DrumsAmoeba::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2DrumsAmoeba::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2DrumsAmoeba::drawActive()
{
    camera.begin();
    {
        /*
        ofEnableLighting();

        pointLight1.enable();
        pointLight2.enable();
        pointLight3.enable();
*/
        
        glPointSize(2.0);
        sphere.setResolution(4);

        ofSetColor(ofColor::white);
        shader.begin();
        {
            shader.setUniformTexture("tex",noiseImage.getTextureReference(),0);
            shader.setUniform1f("offset", offset);

            //noiseImage.getTextureReference().bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            //sphere.draw();
            sphere.drawVertices();
            //sphere.draw();
            //noiseImage.getTextureReference().unbind();
        }
        shader.end();

        if(showNormals)
        {
            // draw normals
            ofSetColor(255,0,0,255);
            sphere.drawNormals(3);
        }
        
        
        // Draw transitioning circle
        if ((currentState == S3ObjStateTransitioning) || (currentState== S3ObjStateInactive))
        {
            // Circle
            ofFill();
            ofDisableLighting();
            ofSetColor(255, 255, 255, int(volumeCircleAlpha));
            ofCircle(objPosition.x, objPosition.y, 0, volumeCircleRadius);
        }


        ofDisableDepthTest();
        //------------------//

        // color image
/*
        ofSetColor(ofFloatColor(1.0,1.0,1.0,ofMap(mouseInteractionX,0.0,1.0,0.0,0.55)));
*/

/*
        float circleSize = ofMap(mouseInteractionX,0.0,1.0,60.0,200);
*/

//        ofSetColor(ofColor::gray);
//        if (pinchEnabled)
//        {
            drawPinchCircle();
            drawPinchColor();
//        }
        drawWhiteCircle();
        drawLoop();

    }
    camera.end();
}

///--------------------------------------------------------------
void S2DrumsAmoeba::volumeChanged(float &newVolume)
{
    
    float toRadius = ofMap(newVolume,0.0,1.0,0,activeCircleRadius);
    float toAlpha = ofMap(newVolume,0.0,1.0,0,activeCircleAlpha);
    float toFrequency = ofMap(newVolume,0.0,1.0,stableNoiseFrequency,18);
    
    // white circle
    Tweenzor::add(&volumeCircleRadius, volumeCircleRadius, toRadius, 0, 0.1, EASE_IN_OUT_SINE);
    Tweenzor::add(&volumeCircleAlpha, volumeCircleAlpha, toAlpha, 0, 0.1, EASE_IN_OUT_SINE);
    Tweenzor::add((float*)&noiseFrequency.get(), noiseFrequency, toFrequency, 0, 0.1, EASE_IN_OUT_SINE);

}


///--------------------------------------------------------------
void S2DrumsAmoeba::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}
