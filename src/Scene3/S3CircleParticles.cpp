//
//  S3ExampleObject.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/5/15.
//
//

#include "S3CircleParticles.h"

#include "ofxTweenzor.h"

#pragma mark - Initialization

///--------------------------------------------------------------
S3CircleParticles::S3CircleParticles(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();

}

///--------------------------------------------------------------
void S3CircleParticles::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

    // Custom object settings go here
    
    gui.add(updateCircle.set("updateCircle",true));
    gui.add(numDotsInCircle.set("numDotsInCircle",100, 0,200));
    gui.add(circleRadius.set("circleRadius",100, 0,200));
    gui.add(updateParticles.set("updateParticles",false));
    gui.add(baseAge.set("baseAge",10, 0,200));

    gui.loadFromFile(settingsPath);
    
    recalculateCircle();

    // PARTICLE SYSTEM SETUP
    int num = 800;
	p.assign(num, demoParticle());
	currentMode = PARTICLE_MODE_REPEL;
	resetParticles();
    particlesState = 0; // no particles
    changeParticleState(0);
    for(int i=0;i<p.size();i++)
    {
        p[i].baseAge = baseAge;
    }
    
    cout << "setup particles done! " << endl;

}

#pragma mark - Basic object methods

///--------------------------------------------------------------
void S3CircleParticles::setup()
{
    S3BaseObj::setup();

    sphere.setRadius(radius);
    sphere.setPosition(objPosition);
    sphere.setResolution(4);

    camera.setTarget(sphere);

    isFirstSetup = false;

    Tweenzor::resetAllTweens();
}

///--------------------------------------------------------------
void S3CircleParticles::initInactive()
{
//    cout << "circlePart :: init inactive" << endl;
    Tweenzor::add(&scaleCircle, 1.0f, 1.1f, 0.0f, 0.7f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&scaleCircle);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3CircleParticles::onCompleteInactive);

    sphereScale = 0;
    
    changeParticleState(0);
    
    resetParticles();

}

///--------------------------------------------------------------
void S3CircleParticles::onCompleteInactive(float* arg)
{
    scaleCircle = 1.0;
    
    if (!shouldChangeState)
    {
        initInactive();
    }
    else
    {
        // PARTICLES
        for(unsigned int i = 0; i < p.size(); i++)
        {
            p[i].reset();
        }
        
        changeParticleState(0);

        changeState();

    }
}

///--------------------------------------------------------------
void S3CircleParticles::updateInactive()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
//    updateActive(); // Delete this line if it needs a custom update
    if(updateCircle) recalculateCircle();
    
    if(updateParticles)
    {
        for(int i=0;i<p.size();i++)
        {
            p[i].baseAge = baseAge;
        }
    }
}

void S3CircleParticles::drawInactive()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------
void S3CircleParticles::initTransitioning()
{
    Tweenzor::add(&sphereScale, 1.0f, 0.0f, 0.0f, 0.8f, EASE_IN_OUT_SINE);
    Tween *tween = Tweenzor::getTween(&sphereScale);
    tween->setRepeat(1, true);
    Tweenzor::addCompleteListener(tween, this, &S3CircleParticles::onCompleteTransitioning);

    nextState = S3ObjStateActive;
    shouldChangeState = true;
    
    for(int i=0;i<p.size();i++)
    {
        p[i].reset();
//        cout << "AAA setting velocity to 10!!" << endl;

//        float velAmmount = 10;
//        
//        p[i].vel.x = ofRandom(-velAmmount, velAmmount);
//        p[i].vel.y = ofRandom(-velAmmount, velAmmount);

    }

    changeParticleState(1);
}

///--------------------------------------------------------------
void S3CircleParticles::onCompleteTransitioning(float* arg)
{
    changeState();
    
    for(unsigned int i = 0; i < p.size(); i++)
    {
        //p[i].reset();
//        float velAmmount = 5;
//        p[i].vel.x = ofRandom(-velAmmount, velAmmount);
//        p[i].vel.y = ofRandom(-velAmmount, velAmmount);

    }

//    cout << "RESETTING ALL PARTICLES ON COMPLETE TRASITION" << endl;

    changeParticleState(1);
    
    

}

///--------------------------------------------------------------
void S3CircleParticles::updateTransitioning()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    
    // PARTICLES
    if(particlesState !=0)
    {
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].setMode(currentMode);
            p[i].update();
        }
        
    }

}

///--------------------------------------------------------------
void S3CircleParticles::drawTransitioning()
{
    drawActive(); // Delete this line if it needs a custom draw
}


///--------------------------------------------------------------
void S3CircleParticles::initActive()
{
    changeParticleState(1);
}

///--------------------------------------------------------------
void S3CircleParticles::updateActive()
{
    // PARTICLES
    if(particlesState !=0)
    {
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].setMode(currentMode);
            p[i].update();
        }
        
    }

}

///--------------------------------------------------------------
void S3CircleParticles::drawActive()
{
//    cout << "currentState : " << currentState << endl;
  
    camera.begin(viewRectangle);
    {
        // PARTICLES
        ofSetColor(255);
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].draw();
        }
        
        // draw circle of points
        ofColor particleColor;
        
//        switch(currentState)
//        {
//            case S3ObjStateInactive:        particleColor = ofColor::red; break;
//            case S3ObjStateTransitioning:   particleColor = ofColor::orange; break;
//            case S3ObjStateActive :         particleColor = ofColor::green; break;
//                
//            default:                        break;
//        }
//        ofSetColor(particleColor);
        
        ofSetColor(255,255,255);
        ofPushMatrix();
        {
            ofTranslate(0.0,objPosition.y);
            //ofRotateZ(ofGetElapsedTimef()*20);
            ofScale(scaleCircle,scaleCircle,scaleCircle);
            circleMesh.drawVertices();
        }
        ofPopMatrix();
        
        // draw white circle
        drawWhiteCircle();
        if (pinchEnabled) drawPinchCircle();

        drawLoop();
    }
    camera.end();
}

///--------------------------------------------------------------
void S3CircleParticles::setPositionFromScreenCoords(int screenX, int screenY)
{
    // baseObj
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);

    // sphere
    sphere.setPosition(objPosition);
    
    // particles
    for(unsigned int i = 0; i < p.size(); i++)
    {
        p[i].setOrigin(objPosition);
    }

}

///--------------------------------------------------------------
void S3CircleParticles::volumeChanged(float &newVolume)
{

    for(unsigned int i = 0; i < p.size(); i++)
    {
        p[i].scale = 3 * newVolume;
    }

}


///--------------------------------------------------------------
void S3CircleParticles::recalculateCircle()
{
    // create circle mesh
    //int     numDotsInCircle = 100;
    //float circleRadius = 100;

    scaleCircle = 1.0 ;
    
    circleMesh.clear();
    
    for(float i=0;i<=numDotsInCircle+1;i++)
    {
        //where we are in pct to the total ?
        float pct = i/float(numDotsInCircle);
        
        ofVec3f aPoint;
        
        float angle = ofMap(i,0,numDotsInCircle,0,2*PI);
        
        aPoint.x = circleRadius * cos(angle);
        aPoint.y = circleRadius * sin(angle);
        aPoint.z = 0;
        
        circleMesh.addVertex(aPoint);
    }

    
}

//--------------------------------------------------------------
void S3CircleParticles::resetParticles()
{
    
	for(unsigned int i = 0; i < p.size(); i++)
    {
		p[i].reset();
	}
    
//    cout << "RESET ALL PARTICLES !!  " << endl;
}

//--------------------------------------------------------------
void S3CircleParticles::changeParticleState(int s)
{
    particlesState = s;
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].state = s;
	}
    
    //cout << "changed PARTICLE state to : " << particlesState << endl;
    
}
