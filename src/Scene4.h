//
//  Scene4.h
//  ConductrEnter
//
//  Created by Miquel Ëngel Soler on 21/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__Scene4__
#define __ConductrEnter__Scene4__

#include <stdio.h>
#include <ofxAppUtils.h>
#include "BaseScene.h"
#include "S4BaseObj.h"

class Scene4 : public BaseScene
{
public:

//    Scene4(const string& name) : BaseScene(name) {}
    Scene4(const string& name);
    virtual ~Scene4();

    void setup();
    void update();
    virtual void drawScene();
    void exit();

private:

    // Touch (currently mouse) events
    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);

    vector<S4BaseObj*> objects;
    unsigned int num_objects;
};

#endif /* defined(__ConductrEnter__Scene4__) */
