#include "UI.h"
#include "OgreApplicationContext.h"

UI* UI::ui_ = nullptr;;

UI::UI(Ogre::RenderWindow* window, SceneManager* scnMgr, RenderQueueListener* newListener)
{
    mWindow = window;
    mScnMgr = scnMgr;
    mNewListener = newListener;

    //TrayManager* TrayMgr, TrayManager* ButtonTrayMgr
   /* mTrayMgr = TrayMgr;
    mButtonTrayMgr = ButtonTrayMgr;
    mTrayMgr->showFrameStats(TL_TOPRIGHT);
    mTrayMgr->toggleAdvancedFrameStats();
    mTime = mTrayMgr->createLabel(TL_TOPRIGHT, "time", "Time: 0", 150);
    mReset = mButtonTrayMgr->createButton(TL_CENTER, "reset", "Reset", 100);
    hideResetButton();*/
}

UI* UI::GetInstance(Ogre::RenderWindow* window, SceneManager* scnMgr, RenderQueueListener* newListener)
{
    if (ui_ == nullptr) {
        ui_ = new UI(window, scnMgr, newListener);
    }
    return ui_;
}

TrayManager* UI::addedTrayMgr(std::string name, bool isVisible)
{
    TrayManager* tempTray;
    tempTray = new OgreBites::TrayManager(name, mWindow);
    mScnMgr->addRenderQueueListener(mNewListener);
    arrayTrayMgr.push_back(tempTray);

    if (!isVisible) {
        tempTray->hideAll();
    }

    return arrayTrayMgr.back();
}

void UI::addedFrameStatsToTray(int whichTray, TrayLocation position, bool showAllStats)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    tempTray->showFrameStats(position);
    if (!showAllStats) {
        tempTray->toggleAdvancedFrameStats();
    }
}

void UI::addedLabelToTary(int whichTray, TrayLocation position, std::string name, std::string caption, float size)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    OgreBites::Label* tempLabel;
    tempLabel = tempTray->createLabel(position, name, caption, size);
    arrayLabel.push_back(tempLabel);
}

void UI::addedButtonToTray(int whichTray, TrayLocation position, std::string name, std::string caption, float size)
{
    TrayManager* tempTray = arrayTrayMgr.at(whichTray);
    OgreBites::Button* tempButton;
    tempButton = tempTray->createButton(position, name, caption, size);
    arrayButton.push_back(tempButton);
}

void UI::setCaptionForLabel(int whichLabel, String newCaption)
{
    arrayLabel.at(whichLabel)->setCaption(newCaption);
}

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