#include "demoParticle.h"

//------------------------------------------------------------------
demoParticle::demoParticle(){
	attractPoints = NULL;
    reset();
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void demoParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void demoParticle::reset()
{

	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
    //origin = ofVec3f(0,0,0);
	pos.x = origin.x;
	pos.y = origin.y;
    particleMaxAge = baseAge + (baseAge/4 * ofRandomf());
    age = particleMaxAge/2 * ofRandomf();
	
    float velAmmount = 5.0;
	vel.x = ofRandom(-velAmmount, velAmmount);
	vel.y = ofRandom(-velAmmount, velAmmount);
	
	frc   = ofPoint(ofRandomf()*0.001,ofRandomf()*0.001,0);
	
	scale = ofRandom(0.125, 0.125);

    drag  = ofRandom(0.998, 0.998);
}

//------------------------------------------------------------------
void demoParticle::update(){
    
    if(state==1)
    {
        float ageSpeed = 1.0;
        age = age + ageSpeed;
        
        if(age>particleMaxAge)
        {
            reset();
        }
        
        if( mode == PARTICLE_MODE_REPEL ){
            ofPoint attractPt(origin.x,origin.y);
            //frc = attractPt-pos;
            
            //let get the distance and only repel points close to the mouse
            float dist = frc.length();
            frc.normalize(); 
            
            //cout << "demoPart : vel " << vel << endl;
            
            vel *= drag;
            
            if( dist < 2500 ){
                vel += -frc * 0.006; //notice the frc is negative
            }else{
                //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
                frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
                frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
                vel += frc * 0.4;
            }
        }
        //2 - UPDATE OUR POSITION
        
        pos += vel;
        
        // UPDATE SCALE WITH A BIT OF SMOOTHING
        float alpha = 0.25;
        scale = scale * (1.0-alpha) + oldScale * alpha;
    }
}

//------------------------------------------------------------------
void demoParticle::draw(){

    float alpha = (age/particleMaxAge);

    ofVec3f posDist;
    float factor;
    factor = ofMap(fabs(pos.x),0.0,20.0,0.0,1.0,true);

    if( mode == PARTICLE_MODE_REPEL ){
		ofSetColor((255 - 255*alpha)*factor,(255 - 255*alpha)*factor,( 255 - 255*alpha)*factor);
	}
    
	ofCircle(pos.x, pos.y, scale + 1.0);
}

//------------------------------------------------------------------
void demoParticle::setOrigin(ofVec3f v)
{
    origin = v;
}
