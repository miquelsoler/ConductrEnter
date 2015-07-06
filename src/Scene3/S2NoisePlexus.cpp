//
//  S2NoisePlexus
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S2NoisePlexus.h"
#include "SettingsManager.h"

///--------------------------------------------------------------
S2NoisePlexus::S2NoisePlexus(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
S2BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S2NoisePlexus::loadSettings()
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
    
    gui.add( plexusMinDistance.set( "plexus min distance",0,0,100) );
    gui.add( plexusMaxDistance.set( "plexus max distance",0,0,100) );
    gui.add( noiseMinDistance.set( "noise min distance",0,0.0,1.0) );
    gui.add( noiseMaxDistance.set( "noise max distance",0,0.0,1.0) );
    gui.add( mode.set("mode",0,0,5));

    
    gui.loadFromFile(settingsPath);
    
    //cout << "Amoeba : stable noise freq. on load : " << noiseFrequency << endl;
    
}

///--------------------------------------------------------------
void S2NoisePlexus::setup()
{
    S2BaseObj::setup();
    
    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(3);
    ofSetCircleResolution(64);

    
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
    }
    
    // PLEXUS MESH
    // printing info
//    cout << "sphere num Vertices:  " << sphere.getMesh().getNumVertices() << endl;
//    cout << "sphere num TexCoords: " << sphere.getMesh().getNumTexCoords() << endl;
//    cout << "sphere num Normals:   " << sphere.getMesh().getNumNormals() << endl;

    plexus.clear();
    plexus.setMode(OF_PRIMITIVE_LINES);
    for(int i=0;i<sphere.getMesh().getNumVertices();i++)
    {
        plexus.addVertex(sphere.getMesh().getVertex(i));
        plexus.addColor(ofFloatColor(1.0,1.0,1.0));
        plexus.addTexCoord(sphere.getMesh().getTexCoord(i));
        plexus.addNormal(sphere.getMesh().getNormal(i));
    }

//    cout << "plexus num Vertices:  " << plexus.getNumVertices() << endl;
//    cout << "plexus num TexCoords: " << plexus.getNumTexCoords() << endl;
//    cout << "plexus num Normals:   " << plexus.getNumNormals() << endl;

    isFirstSetup = false;
    
    // Max offset is the minimum offset applied with volume reaction
    // stable offset is the inactive state one ... it copys from offset at startup (load xml)
    maxOffset = 18;
    stableOffset = offset;
    
    // lights
    pointLight1.setDiffuseColor( ofFloatColor(0, 1.0, 160.0/255.0) );
    pointLight1.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 247.0/255.f, 66.f/255.f, 55.0/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(1.0f, 1.0f, 1.0f));
    
    pointLight3.setDiffuseColor( ofFloatColor(68.0/255.f,187.0/255.f,209.0/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(1.0,1.0,1.0) );
    
    // lights positions
    pointLight1.setPosition(-200 ,200,400);
    pointLight2.setPosition(200 ,0,400);
    pointLight3.setPosition(-200,-200,400);

    
    
    Tweenzor::resetAllTweens();
    
}


///--------------------------------------------------------------
void S2NoisePlexus::initInactive()
{
    
    colorImageAlpha = 0;
    
    //cout << "INIT INACTIVE " << endl;
    inactiveNoiseFrequency = 100;
    inactiveCircleRadius = 0;
    inactiveCircleAlpha = 0;
    
    transitionCircleRadius = 0;
    transitionCircleAlpha = 255;
    activeNoiseFrequency = 120;
    
    maxVolumeCircleRadius = 70;
    maxVolumeCircleAlpha = 250;
    
    maxOffset = 18;
    
    // noise set to original position
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,inactiveNoiseFrequency, 0, 0.3, EASE_IN_OUT_SINE);
    
    // white circle set to original position
    Tweenzor::add(&volumeCircleRadius, volumeCircleRadius, inactiveCircleRadius, 0, 0.6, EASE_IN_OUT_SINE);
    Tweenzor::add(&volumeCircleAlpha, volumeCircleAlpha,  inactiveCircleAlpha,  0, 0.6, EASE_IN_OUT_SINE);
    
}
///--------------------------------------------------------------
void S2NoisePlexus::updateInactive()
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
void S2NoisePlexus::initTransitioning()
{
    //cout << "INIT TRANSITION" << endl;
    float delay = 0.0f;
    float duration = 0.4f;
    
    // noise frequency
    Tweenzor::add((float*)&noiseFrequency.get(), inactiveNoiseFrequency, activeNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&noiseFrequency.get()), this, &S2NoisePlexus::onCompleteTransitioning);
    
    // white circle
    Tweenzor::add(&transitionCircleRadius, 0, maxVolumeCircleRadius, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::add(&transitionCircleAlpha, maxVolumeCircleAlpha, 0.0f, delay, duration, EASE_IN_OUT_SINE);
    
}

///--------------------------------------------------------------
void S2NoisePlexus::updateTransitioning()
{
    //cout << "UPDATE TRANSITION" << endl;
    updateActive(); // Delete this line if it needs a custom update
}

///--------------------------------------------------------------
void S2NoisePlexus::onCompleteTransitioning(float* arg)
{
    
    float delay = 0.0f;
    float duration = 0.4f;
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,inactiveNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&noiseFrequency.get()), this, &S2NoisePlexus::onCompleteTransitioningToActive);
    
    ////cout << "on COMPLETE TRANSITION ... so NEW TWWEEN TO ACTIVE COÑO!!" << endl;
}

///--------------------------------------------------------------
void S2NoisePlexus::onCompleteTransitioningToActive(float* arg)
{
    nextState = S3ObjStateActive;
    shouldChangeState = true;
    changeState();
    
    transitionCircleRadius = 0;
    transitionCircleAlpha = 255;
}

///--------------------------------------------------------------
void S2NoisePlexus::updateActive()
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
                    //noisePixels[((i*100)+j)*1] = 255;
                    //noisePixels[((i*100)+99-j)*1] = 255;
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
    
    
    
    //-------------
    // MESH PLEXUS
    //-------------
    
    // clear indices to be remade each frame
    plexus.getIndices().clear();
    nothingToDraw = false;
    
    for(int i=0;i<sphere.getMesh().getNumVertices();i++)
    {
        ofVec2f v = plexus.getTexCoord(i);
        
        ofFloatColor col = noiseImage.getColor(v.x*100,v.y*100);
        
        float offs = 100.0;
        
        // add noise to vertex normal and offset
        ofVec3f vert = sphere.getMesh().getVertex(i) + plexus.getNormal(i)*offset*col.r + objPosition;
        plexus.setVertex(i, vert);
        
        ofColor cc = ofColor(255,i,0);
        plexus.setColor(i,cc);
        plexus.setColor(i,col);

        
        int numVerts = plexus.getNumVertices();
        ofVec3f verta = plexus.getVertex(i);
        for (int b=i+1; b<numVerts; ++b)
        {
            ofVec3f vertb = plexus.getVertex(b);
            float distance = verta.distance(vertb);
            //if ((distance > plexusMinDistance) && (distance < plexusMaxDistance) )
            if((col.r>noiseMinDistance)&&(col.r<noiseMaxDistance) && (distance > plexusMinDistance) && (distance < plexusMaxDistance))
            {
                switch(mode)
                {
                    case 0:
                        
                        plexus.addIndex(i);
                        plexus.addIndex(b);
                        
                        break;
                        
                    case 1:
                        
                        if(ofRandomf()>0.5) plexus.addIndex(i);
                        if(ofRandomf()>0.5) plexus.addIndex(b);
                        
                        break;
                        
                    default: break;
                }
            }
        }
        
        
        //cout << col << endl;
        
        //cout << v << endl;
    }
    if(plexus.getIndices().size()>0) plexus.setMode(OF_PRIMITIVE_LINES);
    else if (plexus.getIndices().size()==0)
    {
        nothingToDraw = true;
    }
    
    
    

}

///--------------------------------------------------------------
void S2NoisePlexus::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2NoisePlexus::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}

///--------------------------------------------------------------
void S2NoisePlexus::drawActive()
{
    ofEnableDepthTest();
    
    camera.begin(viewRectangle);
    {
//        glPointSize(2.0);
//        sphere.setset(3);
        
        ofSetLineWidth(1.0);
        
        ofSetColor(ofColor::white);
        
        //shader.begin();
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
        //shader.end();
        
        // PLEXUS MESH
        if (!nothingToDraw) plexus.draw();
        
        
        
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
    ofDisableDepthTest();
    
    //noiseImage.draw(0,0,100,100);
}

///--------------------------------------------------------------
void S2NoisePlexus::volumeChanged(float &newVolume)
{
    
    float toRadius = ofMap(newVolume,0.0,1.0,0, maxVolumeCircleRadius);
    float toAlpha = ofMap(newVolume,0.0,1.0,0, maxVolumeCircleAlpha);
    float toFrequency = ofMap(newVolume,0.0,1.0,0,inactiveNoiseFrequency);
    float toOffset = ofMap(newVolume,0.0,1.0,maxOffset,stableOffset);
    // white circle
    //    Tweenzor::add(&volumeCircleRadius, volumeCircleRadius, toRadius, 0, 0.1, EASE_IN_OUT_SINE);
    //    Tweenzor::add(&volumeCircleAlpha, volumeCircleAlpha, toAlpha, 0, 0.1, EASE_IN_OUT_SINE);
    //    Tweenzor::add((float*)&noiseFrequency.get(), noiseFrequency, toFrequency, 0, 0.1, EASE_IN_OUT_SINE);
    
    volumeCircleRadius = toRadius;
    volumeCircleAlpha = toAlpha;
    //noiseFrequency = toFrequency;
    offset=toOffset;
}


///--------------------------------------------------------------
void S2NoisePlexus::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);
    
    sphere.setPosition(objPosition);
    

}
