#include "UI.h"
#include "OgreApplicationContext.h"

UI* UI::ui_ = nullptr;;

/// The defualt conconstructor
/// 
/// @param: a Oger::window
/// @param: a Oger::SceneManager
/// @param: a Oger::RenderQueueListener
UI::UI(Ogre::RenderWindow* window, SceneManager* scnMgr, RenderQueueListener* newListener)
{
    mWindow = window;
    mScnMgr = scnMgr;
    mNewListener = newListener;
}

/// Used to get a single instance of the UI class
/// 
/// @param: a Oger::window
/// @param: a Oger::SceneManager
/// @param: a Oger::RenderQueueListener
/// @returns the created UI.
UI* UI::GetInstance(Ogre::RenderWindow* window, SceneManager* scnMgr, RenderQueueListener* newListener)
{
    if (ui_ == nullptr) {
        ui_ = new UI(window, scnMgr, newListener);
    }
    return ui_;
}

/// Used create a new tray
/// 
/// Can create multiple trays to differnet UI elements 
/// @param: a string
/// @param: a bool
/// @returns the created tray
TrayManager* UI::addedTrayMgr(std::string name, bool isVisible)
{
    TrayManager* tempTray;
    tempTray = new OgreBites::TrayManager(name, mWindow);
    mScnMgr->addRenderQueueListener(mNewListener);
    arrayTrayMgr.push_back(tempTray);
    //if visable in application
    if (!isVisible) {
        tempTray->hideAll();
    }

    return arrayTrayMgr.back();
}

/// Add FrameStats to tray
/// 
/// FrameStats is a UI element that come with ogre
/// @param: a int of which tray in the array
/// @param: a OgreBites::TrayLocation 
/// @param: a bool 
void UI::addedFrameStatsToTray(int whichTray, TrayLocation position, bool showAllStats)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    tempTray->showFrameStats(position);
    if (!showAllStats) {
        tempTray->toggleAdvancedFrameStats();
    }
}

/// Add OgreBites::Label to tray
/// 
/// @param: a int of which tray in the array
/// @param: a OgreBites::TrayLocation 
/// @param: a string for unique identification
/// @param: a string for caption
/// @param: a float for size of label
void UI::addedLabelToTary(int whichTray, TrayLocation position, std::string name, std::string caption, float size)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    OgreBites::Label* tempLabel;
    tempLabel = tempTray->createLabel(position, name, caption, size);
    arrayLabel.push_back(tempLabel);
}

/// Add OgreBites::Button to tray
/// 
/// @param: a int of which tray in the array
/// @param: a OgreBites::TrayLocation 
/// @param: a string for unique identification
/// @param: a string for caption
/// @param: a float for size of button
void UI::addedButtonToTray(int whichTray, TrayLocation position, std::string name, std::string caption, float size)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    OgreBites::Button* tempButton;
    tempButton = tempTray->createButton(position, name, caption, size);
    arrayButton.push_back(tempButton);
}

/// set Labels caption 
/// 
/// @param: a int of which label in the array
/// @param: a string for caption
void UI::setCaptionForLabel(int whichLabel, String newCaption)
{
    arrayLabel.at(whichLabel)->setCaption(newCaption);
}

/// set tray  visability  
/// 
/// @param: a int of which tray in the array
/// @param: a bool isVisable
void UI::setTrayVisibility(int whichTray, bool isVisible)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    if (isVisible) {
        tempTray->showAll();
    }
    else {
        tempTray->hideAll();
    }
}

/// get button state  
/// 
/// @param: a int of which button in the array
/// @returns a bool is being pressed or not
bool UI::getIsButtonPressed(int whichButton)
{
    Button* tempButton = arrayButton.at(whichButton);
    
    if (tempButton->getState() == BS_DOWN) {
        return true;
    }
    else
    {
        return false;
    } 
}