//
//  S3DrumsAmoeba.cpp
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 24/5/15.
//
//

#include "S3DrumsAmoeba.h"

///--------------------------------------------------------------
S3DrumsAmoeba::S3DrumsAmoeba(unsigned int numObjects, unsigned int objectIndex, float _viewOriginX, float _viewWidth, string _settingsPath) :
    S3BaseObj(numObjects, objectIndex, _viewOriginX, _viewWidth, _settingsPath)
{
    loadSettings();
}

///--------------------------------------------------------------
void S3DrumsAmoeba::loadSettings()
{
    if (settingsPath.empty()) return;
    S3BaseObj::initSharedSettings();

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
}

///--------------------------------------------------------------
void S3DrumsAmoeba::setup()
{
    S3BaseObj::setup();

    ofSetSmoothLighting(true);
    ofSetVerticalSync(true);
    ofSetCircleResolution(64);
    glPointSize(2.0);

    sphere.setRadius(radius);
    sphere.setResolution(4);
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
    shader.load("objects/drums_amoeba/shaders/shader");
    ofDisableArbTex();

    // color image: candidat a codi comœ
    imgColorsCircle.loadImage("objects/color_circle.png");

    /// CREATE NOISE IMAGE
    noiseImage.allocate(100, 100, OF_IMAGE_GRAYSCALE);
    noisePixels.allocate(100, 100, 1);

    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            noisePixels[((j*100)+i)*1] = 255;
        }
    }
    noiseImage.setFromPixels(noisePixels);
}

///--------------------------------------------------------------
void S3DrumsAmoeba::update()
{
    S3BaseObj::update();

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
void S3DrumsAmoeba::volumeChanged(float &newVolume)
{
}

///--------------------------------------------------------------
void S3DrumsAmoeba::draw()
{
    S3BaseObj::draw();

//    ofEnableDepthTest();

    camera.begin(viewRectangle);
    {
        ofEnableLighting();

        pointLight1.enable();
        pointLight2.enable();
        pointLight3.enable();

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
            ofSetColor(255,0,0,128);
            sphere.drawNormals(3);
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

        ofSetColor(ofColor::gray);
        imgColorsCircle.setAnchorPercent(0.5,0.5);
        float circleSize = 40.0;
//        imgColorsCircle.draw(objPosition.x, objPosition.y, circleSize, circleSize);

        drawWhiteCircle();
        if (pinchEnabled) drawPinchCircle();
        drawLoop();

    }
    camera.end();
}

///--------------------------------------------------------------
void S3DrumsAmoeba::setPositionFromScreenCoords(int screenX, int screenY)
{
    S3BaseObj::setPositionFromScreenCoords(screenX, screenY);

    sphere.setPosition(objPosition);
}
