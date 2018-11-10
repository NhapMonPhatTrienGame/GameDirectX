#ifndef _FRAME_WORK_H
#define _FRAME_WORK_H

#include <d3d9.h>
#include "Game.h"

#define WIN32_LEARN_AND_MEAN

class FrameWork
{
	Game* _game;
	LPCSTR _applicationName;
	HINSTANCE _hInstance;
	HWND _hWnd;

	bool CreateDXWindow(const char* windowTitle, int x, int y, int width, int height);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:

	FrameWork();
	~FrameWork();

	bool Initialize();
	void Run();
};

#endif