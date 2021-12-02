#include "Input.h"
#include "OgreApplicationContext.h"
#include <iostream>

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
    currentKeyPtr = &currentKey;
    std::cout << currentKey.keysym.sym << std::endl;
    return true;
}

bool Input::checkIfKeyBeingPressed(char keyType)
{
    if (currentKeyPtr == nullptr)
        return false;
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
    if (currentKeyPtr == nullptr)
        return false;
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
    currentKeyPtr = nullptr;
}




