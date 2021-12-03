#pragma once
#ifndef UI_H
#define UI_H

#include "Ogre.h"
#include "OgreTrays.h"

using namespace Ogre;
using namespace OgreBites;
/// This class is used to create and control UI elements
class UI
{
protected:
    UI(Ogre::RenderWindow* window, SceneManager* scnMgr, RenderQueueListener* newListener);
    virtual ~UI() {};
    static UI* ui_;
    
public:    
    UI(UI& other) = delete;
    void operator=(const UI&) = delete;
    static UI* GetInstance(Ogre::RenderWindow* window, SceneManager* scnMgr, RenderQueueListener* newListener);
    TrayManager* addedTrayMgr(std::string name, bool isVisible);
    void addedFrameStatsToTray(int whichTray, TrayLocation position, bool showAllStats);
    void addedLabelToTary(int whichTray, TrayLocation position, std::string name, std::string caption, float size);
    void addedButtonToTray(int whichTray, TrayLocation position, std::string name, std::string caption, float size);
    void setCaptionForLabel(int whichLabel, String newCaption);
    void setTrayVisibility(int whichLabel, bool isVisible);
    bool getIsButtonPressed(int whichButton);

private:
    std::vector<TrayManager*> arrayTrayMgr;
    Ogre::RenderWindow* mWindow; 
    SceneManager* mScnMgr; 
    RenderQueueListener* mNewListener;
    std::vector<Label*> arrayLabel;
    std::vector<Button*> arrayButton;
};

#endif 
