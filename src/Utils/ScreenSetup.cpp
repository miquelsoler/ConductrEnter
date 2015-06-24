//
//  ScreenSetup.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 24/6/15.
//
//

#include "ScreenSetup.h"

#include "ofAppGLFWWindow.h"
#include "Defaults.h"
#include "SettingsManager.h"

void ScreenSetup::setScreenMode(ScreenMode mode)
{
    switch (mode)
    {
        case SCREENMODE_WINDOW:
            setModeWindow();
            break;
        case SCREENMODE_FULL:
            setModeFull();
            break;
        case SCREENMODE_DISPLAX:
            setModeDisplax();
            break;
        default:
            break;
    }
}

void ScreenSetup::switchMode()
{
    ScreenMode newMode = ScreenMode((currentMode + 1) % SCREENMODE_NUMMODES);
    setScreenMode(newMode);
}

void ScreenSetup::setModeWindow()
{
    ofSetFullscreen(false);
    ofSetWindowShape(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    currentMode = SCREENMODE_WINDOW;
}

void ScreenSetup::setModeFull()
{
    ofSetFullscreen(true);
    currentMode = SCREENMODE_FULL;
}

void ScreenSetup::setModeDisplax()
{
    ofSetFullscreen(true);
    int windowWidth = SettingsManager::getInstance().displaxWidth * 2;
    int windowHeight = SettingsManager::getInstance().displaxHeight;
    ofSetWindowShape(windowWidth, windowHeight);
    ofVec2f mainScreenOffset = getMainScreenOrigin();
    ofSetWindowPosition(mainScreenOffset.x, mainScreenOffset.y);

    currentMode = SCREENMODE_DISPLAX;
}

ofVec2f ScreenSetup::getMainScreenOrigin()
{
    ofAppBaseWindow * win = ofGetWindowPtr();

    if(dynamic_cast<ofAppGLFWWindow*>(win) != NULL){

        ofAppGLFWWindow *windowP = (ofAppGLFWWindow *)ofGetWindowPtr();
        GLFWwindow * windowPtr = windowP->getGLFWWindow();
        int numberOfMonitors;
        GLFWmonitor** monitors = glfwGetMonitors(&numberOfMonitors);

        int xW;	int yW;
        glfwGetWindowPos(windowPtr, &xW, &yW);

        for (int iC = 0; iC < numberOfMonitors; iC++){
            int xM; int yM;
            glfwGetMonitorPos(monitors[iC], &xM, &yM);
            const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[iC]);
            ofRectangle monitorRect(xM, yM, desktopMode->width, desktopMode->height);
            if (monitorRect.inside(xW, yW)){
                return ofVec2f(xM, yM);
                break;
            }
        }
    }
    return ofVec2f();
}

ofVec2f ScreenSetup::getLeftmostMonitorCoord()
{
    ofAppBaseWindow * win = ofGetWindowPtr();
    if(dynamic_cast<ofAppGLFWWindow*>(win) != NULL){

        ofAppGLFWWindow *windowP = (ofAppGLFWWindow *)ofGetWindowPtr();
        GLFWwindow * windowPtr = windowP->getGLFWWindow();
        int numberOfMonitors;
        GLFWmonitor** monitors = glfwGetMonitors(&numberOfMonitors);

        float xMin = FLT_MAX;
        float yMin = FLT_MAX;
        int xW;	int yW;
        glfwGetWindowPos(windowPtr, &xW, &yW);

        for (int iC = 0; iC < numberOfMonitors; iC++){
            int xM; int yM;
            glfwGetMonitorPos(monitors[iC], &xM, &yM);
            if (xMin > xM) xMin = xM;
            if (yMin > yM) yMin = yM;
        }
        return ofVec2f(xMin, yMin);
    }
    return ofVec2f();
}