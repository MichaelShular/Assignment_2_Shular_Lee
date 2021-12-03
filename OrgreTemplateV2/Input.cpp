#include "Input.h"
#include "OgreApplicationContext.h"

Input* Input::input_ = nullptr;;

Input::Input(Root* root)
{
    mRoot = root; 
}

Input* Input::GetInstance(Root* root)
{
    if (input_ == nullptr) {
        input_ = new Input(root);
    }
    return input_;
}

bool Input::Update(const OgreBites::KeyboardEvent& evt)
{
    currentKey = evt;
    return true;
}

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

void Input::reset()
{
    currentKey.keysym.sym = OgreBites::SDLK_F11;
}





