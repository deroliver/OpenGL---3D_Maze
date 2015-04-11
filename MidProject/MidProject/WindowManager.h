#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <string>
#include <fstream>
#include "InputManager.h"



class WindowManager {

public:

	virtual ~WindowManager() {}

	virtual int Initialize(int width, int height, std::string Title, bool FullScreen = false) = 0;

	virtual void SwapTheBuffers() = 0;

	virtual bool ProcessInput(bool continueGame) = 0;

	virtual void Destroy() = 0;

	virtual InputManager *GetInputManager() { return &InputManager; }

protected:

	InputManager InputManager;
};

#endif