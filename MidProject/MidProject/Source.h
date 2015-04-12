#ifndef SOURCE_H_
#define SOURCE_H_

#include "Camera.h"
#include "WindowManager.h"

class Source {

public:

	static const int ScreenWidth = 1366;
	static const int ScreenHeight = 768;

	Source() {}
	~Source() { Destroy(); }

	int Main();

	WindowManager *GetWindowManager() { return WindowManager; }
	void SetWindowManager(WindowManager *WM) { WindowManager = WM; }


	Camera *GetCamera() { return Camera; }
	void SetCamera(Camera *C) { Camera = C; }


	void Initialize();

	void GameLoop();

	void Destroy();

protected:

	WindowManager *WindowManager;

	Camera *Camera;
};

#endif