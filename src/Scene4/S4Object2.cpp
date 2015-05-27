//
//  S4Object2.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S4Object2.h"

void S4Object2::setup()
{
    if (!isGLSetup)
    {
        // Shader and mesh setup

        // We need to set a few extra params for the geometry shader, in this order.
        grassShader.setGeometryInputType(GL_LINES);
        grassShader.setGeometryOutputType( GL_TRIANGLES );
        grassShader.setGeometryOutputCount( 3 * 6 * 6  ); // GTX 970 has a limit of 128 vertices output per shader limiting us to 3 * 6 * 6, investigate..
        grassShader.load("Shaders/Tendrils/GL2/Tendrils.vert", "Shaders/Tendrils/GL2/Tendrils.frag", "Shaders/Tendrils/GL2/Tendrils.geom");

        computeMesh();
        isGLSetup = true;
    }

    // Camera settings

    camera.setPosition( 0, 0.5, 10.0 );
    camera.setTarget(ofPoint(0,0,0));
    camera.setDistance(30);
    camera.setNearClip(0.01f);

    // Loop arc settings
    loopRadius = 30;
}

void S4Object2::update()
{
#ifdef OF_DEBUG
    // Update object parameters from XML
    camera.setDistance(camDistance);
#endif
}

void S4Object2::draw()
{
    ofEnableDepthTest();

    ofDisableLighting();

    camera.begin(viewRectangle);

    drawLoop();
    drawTendrils( &camera );

    camera.end();

    ofDisableDepthTest();
    ofEnableBlendMode( OF_BLENDMODE_ALPHA );
    ofSetColor( ofColor::white );

#ifdef OF_DEBUG
    gui.draw();
#endif
}

#pragma mark - Private

void S4Object2::computeMesh()
{
    placementResolution = 21;
    placementSize = 3.466f;
    placementNoiseSpaceFrequency = 0.510083f;
    placementBottomThreshold = 0;

    stalkRadius = 0.276739f;
    stalkHeight = 8.20002f;
    swayingMaxAngle = 19.8f;
    swayingTimeScale = 2.06003f;
    swayingNoiseSpaceFrequency = 0.333427f;
    swayingTimeMaxDifference = 2.03339f;

    ofMesh srcMesh = ofMesh::sphere( placementSize, placementResolution, OF_PRIMITIVE_TRIANGLES );
    // Todo: swap in other meshes

    grassMesh.clear();
    grassMesh.setMode( OF_PRIMITIVE_LINES );

    if( srcMesh.getNumVertices() != srcMesh.getNumNormals() )
    {
        ofLogError() << "void ofApp::computeMesh() Hey, this is not going to work if we don't have a normal for each vertex.";
    }
    else
    {
        vector<ofVec3f>& vertices = srcMesh.getVertices();
        vector<ofVec3f>& normals = srcMesh.getNormals();
        for( int i = 0; i < vertices.size(); i++ )
        {
            ofVec3f vertexPos = vertices.at(i);
            ofVec3f perlinPos = vertexPos * placementNoiseSpaceFrequency; //ofMap( mx, 0, 1,  0.01, 5);

            float placementPerlinVal = ofNoise( perlinPos.x, perlinPos.y, perlinPos.z );

            // Remap the number back to 0..1 taking our bottom threshold into account and clamping
            placementPerlinVal= ofMap( placementPerlinVal, placementBottomThreshold, 1,	0, 1, true );

            if( placementPerlinVal > 0 )
            {
                grassMesh.addVertex( vertexPos );
                grassMesh.addVertex( vertexPos + ( normals[i] * placementPerlinVal) ); // the normal has a length we later use to module tendril height
            }
        }
    }
}

void S4Object2::drawTendrils( ofCamera* _camera )
{
    float mx = ofMap( ofGetMouseX(), 0, ofGetWidth(),   0, 1 );
    float my = ofMap( ofGetMouseY(), 0, ofGetHeight(),  0, 1 );

    grassShader.begin();

    grassShader.setUniform1f("timeSecs", ofGetElapsedTimef() );

    grassShader.setUniform3fv( "cameraWorldPos", _camera->getGlobalPosition().getPtr() );

    grassShader.setUniform1f("stalkRadius", stalkRadius );
    grassShader.setUniform1f("stalkHeight", stalkHeight );

    grassShader.setUniform1f("animationTimeMaxDifference", swayingTimeMaxDifference );

    grassShader.setUniform1f("stalkSwayingMaxAngle", ofDegToRad(swayingMaxAngle) * 0.5f );

    grassShader.setUniform1f("grassSwayingTimeScale", swayingTimeScale );
    grassShader.setUniform1f("grassSwayingNoiseFrequency", swayingNoiseSpaceFrequency );

    ofSetColor( ofColor::white );
    
    grassMesh.draw();
    
    grassShader.end();
}

void S4Object2::loadSettings()
{
    gui.setup("Settings");
    gui.add(camDistance.set("Camera_Distance", 0, 0, 200));
    gui.add(loopRadius.set("Loop_Radius", 0, 0, 100));

    gui.loadFromFile(settingsPath);
}
