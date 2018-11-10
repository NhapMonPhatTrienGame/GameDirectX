#include "Framework.h"
#include "dxgraphics.h"

#include <iostream>
#include "GameTime.h"
using namespace std;


FrameWork::FrameWork()
{
	_game = new Game();
}

FrameWork::~FrameWork()
{
	if (FULL_SCREEN)
		ChangeDisplaySettings(NULL, 0);

	UnregisterClass(_applicationName, _hInstance);
	_hInstance = NULL;
}

bool FrameWork::Initialize()
{
	return CreateDXWindow(APP_TITLE, CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void FrameWork::Run()
{
	_game->Game_Loop();
}


bool FrameWork::CreateDXWindow(const char* windowTitle, int x, int y, int width, int height)
{
	WNDCLASSEX wc;

	// Register windows
	_applicationName = windowTitle;
	_hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _applicationName;
	wc.hIconSm = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClassEx failed", "Error", MB_OK);
		return false;
	}

	//Full Screen
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	DWORD style;

	if (FULL_SCREEN)
	{
		DEVMODE deviceModeSetting;
		memset(&deviceModeSetting, 0, sizeof(deviceModeSetting));
		deviceModeSetting.dmSize = sizeof(deviceModeSetting);
		deviceModeSetting.dmPelsWidth = unsigned long(screenWidth);
		deviceModeSetting.dmPelsHeight = unsigned long(screenHeight);
		deviceModeSetting.dmBitsPerPel = 32;
		deviceModeSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&deviceModeSetting, CDS_FULLSCREEN);
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		screenHeight = height;
		screenWidth = width;
		style = WS_OVERLAPPEDWINDOW;
	}

	_hWnd = CreateWindow(windowTitle, windowTitle,
		style, x, y, width, height, NULL, NULL, _hInstance, NULL);

	if (!_hWnd)
	{
		MessageBox(NULL, "CreateWindowEx failed", "Error", MB_OK);
		PostQuitMessage(0);
		return false;
	}

	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);

	if (!_game->getGraphics()->Init_DirectX3D(_hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN))
	{
		MessageBox(NULL, "Error initializing Direct3D", "Error", MB_OK);
		return false;
	}

	if (!_game->Game_Init(_hWnd))
	{
		MessageBox(NULL, "Error initializing the game", "Error", MB_OK);
		return false;
	}

	return true;
}

LRESULT FrameWork::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		DestroyWindow(hWnd);
		break;
	}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;

}