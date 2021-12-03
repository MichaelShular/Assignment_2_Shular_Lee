#include "Input.h"
#include "OgreApplicationContext.h"

Input* Input::input_ = nullptr;;

/// The defualt conconstructor
/// 
/// @param: a Oger::Root
Input::Input(Root* root)
{
    mRoot = root; 
}
/// Used to get a single instance of the Input class
/// 
/// @param:  a Oger::Root
/// @returns the created Game.
Input* Input::GetInstance(Root* root)
{
    if (input_ == nullptr) {
        input_ = new Input(root);
    }
    return input_;
}

/// Update which was the last key pressed in this frame 
/// 
/// @param:  a OgreBites::KeyboardEvent&
/// @returns a bool
bool Input::Update(const OgreBites::KeyboardEvent& evt)
{
    currentKey = evt;
    return true;
}

/// Check if inputed key was pressed
/// 
/// @param:  a char of key need to be ckecked
/// @returns a bool
bool Input::checkIfKeyBeingPressed(char keyType)
{
    if (currentKey.keysym.sym == keyType) {
        return true;
    }
    else
    {
        return false;
    }
}

/// Check if inputed key was pressed
/// 
/// Used for OgreBites enum of differnt keys
/// @param:  a int of key need to be ckecked
/// @returns a bool
bool Input::checkIfKeyBeingPressed(int keyType)
{
    if (currentKey.keysym.sym == keyType) {
        return true;
    }
    else
    {
        return false;
    }
}

/// Reset currentKey
/// 
/// Put at the end of update and use a button that the game is not using
void Input::reset()
{
    currentKey.keysym.sym = OgreBites::SDLK_F11;
}





