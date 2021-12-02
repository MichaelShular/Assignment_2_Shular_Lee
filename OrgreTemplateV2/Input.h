#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "Ogre.h"
#include "OgreInput.h"

using namespace Ogre;

class Input {
protected:
	Input(Root* root);
	~Input() {};

	static Input* input_;
public:
	Input(Input& other) = delete;
	void operator=(const Input&) = delete;
	static Input* GetInstance(Root* root);

	bool Update(const OgreBites::KeyboardEvent& evt);

	bool checkIfKeyBeingPressed(char keyType);
	bool checkIfKeyBeingPressed(int keyType);

	void reset();

private:
	Root* mRoot;
	OgreBites::KeyboardEvent currentKey;
};

#endif