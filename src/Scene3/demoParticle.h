#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

class demoParticle{

	public:
		demoParticle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
        float oldScale;
		
		particleMode mode;
		
		vector <ofPoint> * attractPoints;
    
    /// ELOI
    float                   baseAge;
    float                   age;
    ofVec3f                 origin;
    ofParameter<float>		particleMaxAge;
    int                     state;

    void setOrigin(ofVec3f v);
    
    
};