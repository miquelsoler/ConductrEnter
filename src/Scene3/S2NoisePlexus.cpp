//
//  S2NoiseSphere.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 24/5/15.
//
//

#include "S2NoisePlexus.h"

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
    gui.add( noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 4096.0f ) );
    gui.add( offset.set( "offset",0,-200,200) );
    gui.add( mode.set( "mode",0,0,3) );

    gui.add( doThreshold.set( "Threshold", false ) );
    gui.add( thresholdLow.set( "Treshold Low", 0, 0, 40 ) );
    gui.add( thresholdHigh.set( "Treshold High", 40, 0, 40 ) );
    gui.add( plexusMinDistance.set( "plexus min distance",0,0,20) );
    gui.add( plexusMaxDistance.set( "plexus max distance",0,0,20) );
    gui.add( noiseMinDistance.set( "noise min distance",0,0.0,1.0) );
    gui.add( noiseMaxDistance.set( "noise max distance",0,0.0,1.0) );

    gui.loadFromFile(settingsPath);
    
    // MESH
    dontDraw=false;
    sphere.setResolution(3);

    plexus.setMode(OF_PRIMITIVE_LINES);
    for(int i=0;i<sphere.getMesh().getNumVertices();i++)
    {
        plexus.addVertex(sphere.getMesh().getVertex(i));
    }

}

///--------------------------------------------------------------
void S2NoisePlexus::setup()
{
    S2BaseObj::setup();

    ofSetSmoothLighting(true);
    ofSetVerticalSync(true);

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(3);

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

        vertexOffset = 0;
        vertexNormals = sphere.getMesh().getNormals();
        vertexOriginals = sphere.getMesh().getVertices();
    }

    isFirstSetup = false;

    Tweenzor::resetAllTweens();

}

///--------------------------------------------------------------
void S2NoisePlexus::initInactive()
{
    stableOffset = 6;
    stableNoiseFrequency = 50;
    activeOffset = 25;
    activeNoiseFrequency = 1000;
 
    float delay = 0.0f;
    float duration = 0.8f;
    
    // noise frequency reset
    //Tweenzor::add((float*)&noiseFrequency.get(), noiseFrequency, stableNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);
    // offset reset
    //Tweenzor::add((float*)&offset.get(), offset, stableOffset, delay, duration, EASE_IN_OUT_SINE);

    
}

///--------------------------------------------------------------
void S2NoisePlexus::updateInactive()
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
void S2NoisePlexus::initTransitioning()
{
//    cout << "INIT TRANSITION" << endl;
    
    float delay = 0.0f;
    float duration = 0.3f;
    
    // noise frequency
    //Tweenzor::add((float*)&offset.get(), stableOffset, activeOffset, delay, duration, EASE_IN_OUT_SINE);
    //Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&offset.get()), this, &S2NoisePlexus::onCompleteTransitioning);
    
}


///--------------------------------------------------------------
void S2NoisePlexus::updateTransitioning()
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
void S2NoisePlexus::onCompleteTransitioning(float* arg)
{
//    cout << " ON COMPLETE TRANSITIONING" << endl;
    
    float delay = 0.0f;
    float duration = 0.3f;
    
    //Tweenzor::add((float*)&offset.get(),offset ,stableOffset, delay, duration, EASE_IN_OUT_SINE);
    //Tweenzor::addCompleteListener(Tweenzor::getTween((float*)&offset.get()), this, &S2NoisePlexus::onCompleteToActive);

    
}

///--------------------------------------------------------------
void S2NoisePlexus::onCompleteToActive(float* arg)
{
    float delay = 0.0f;
    float duration = 0.2f;
    
    Tweenzor::add((float*)&noiseFrequency.get(),noiseFrequency ,activeNoiseFrequency, delay, duration, EASE_IN_OUT_SINE);

//    cout << "ON COMPLETE TO ACTIVE" << endl;
    nextState = S3ObjStateActive;
    shouldChangeState = true;
    
}

///--------------------------------------------------------------
void S2NoisePlexus::initActive()
{
//    cout << " INIT ACTIVE !!!! " << endl;
    
}


///--------------------------------------------------------------
void S2NoisePlexus::updateActive()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    
    sphere.rotate(0.3, 0.0, 1.0, 0.0);

    // perlin noise
    float time = ofGetElapsedTimef();

    // MESH and noise
    dontDraw=false;
    plexus.getIndices().clear();
    
    for(int i=0;i<vertexOriginals.size();i++)
    {
        switch (mode)
        {
            case 0 :
                vertexNoise = ofSignedNoise(i/noiseFrequency,time/tempo);
                break;
            case 1 :
                vertexNoise = ofNoise(i / noiseFrequency,vertexOriginals.size()-i / noiseFrequency,time/tempo );
                break;
            case 2 :
                vertexNoise = ofNoise(i / noiseFrequency ,(i+1)%20/ noiseFrequency,time/tempo );
                break;
            case 3 :
                vertexNoise = ofNoise(i/noiseFrequency*(time/tempo));
                break;
        }
        
        vertexOffset = vertexNoise * offset;
        
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
        
        ofVec3f newPos = vertexOriginals[i]; //+ vertexOffset * vertexNormals[i];
        sphere.getMesh().setVertex(i, newPos);
        
        /////////////
        // MESH
        /////////////
        
        plexus.setVertex(i,sphere.getMesh().getVertex(i) + sphere.getPosition() + vertexOffset * vertexNormals[i]);
        //plexus.setColor(i, ofFloatColor(1.0,1.0,1.0));
        
        
        int numVerts = sphere.getMesh().getNumVertices();
        ofVec3f verta = plexus.getVertex(i);
        for (int b=i+1; b<numVerts; ++b)
        {
            ofVec3f vertb = plexus.getVertex(b);
            float distance = verta.distance(vertb);
            //if ((distance > plexusMinDistance) && (distance < plexusMaxDistance) )
            if((vertexNoise>noiseMinDistance)&&(vertexNoise<noiseMaxDistance) && (distance > plexusMinDistance) && (distance < plexusMaxDistance))
            {
                plexus.addIndex(i);
                plexus.addIndex(b);
            }
        }
        
        
        /////////////
        
    }
    
    if(plexus.getIndices().size()>0) plexus.setMode(OF_PRIMITIVE_LINES);
    else if (plexus.getIndices().size()==0)
    {
        dontDraw = true;
    }


/*
    // update light colors
    pointLight1.setDiffuseColor( ofFloatColor(    ofMap(mouseInteractionX,0.0,1.0,1.0,0.0),     ofMap(mouseInteractionX,0.0,1.0,1.0,1.0),     ofMap(mouseInteractionX,0.0,1.0,1.0,160.0/255.0)) );
    pointLight2.setDiffuseColor( ofFloatColor(  ofMap(mouseInteractionX,0.0,1.0,1.0,247.0/255.f), ofMap(mouseInteractionX,0.0,1.0,1.0,66.f/255.f), ofMap(mouseInteractionX,0.0,1.0,1.0,55.0/255.f) ));
    pointLight3.setDiffuseColor( ofFloatColor(ofMap(mouseInteractionX,0.0,1.0,1.0,68.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,187.0/255.f),ofMap(mouseInteractionX,0.0,1.0,1.0,209.0/255.f)) );
*/
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

        ofSetColor(ofColor::white);

        /// PLEXUS
        if(!dontDraw) plexus.draw();

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
void S2NoisePlexus::setPositionFromScreenCoords(int screenX, int screenY)
{
    S2BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}

///--------------------------------------------------------------
void S2NoisePlexus::volumeChanged(float &newVolume)
{
    float newOffset = ofMap(newVolume,0.0,1.0,stableOffset,40.0);
    Tweenzor::add((float*)&offset.get(),offset ,newOffset, 0, 0.1, EASE_IN_OUT_SINE);
}
