﻿#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <sstream>
#include <windowsx.h>
#include "GameComponents/GameGlobal.h"
#include "GameComponents/Game.h"
#include "GameControllers/SceneManager.h"

using namespace std;

#define WIN_NAME "Game DirectX"
#define WIN_TITLE "Game DirectX"
#define FPS 60
#define KEYBOARD_BUFFERED_SIZE 1024

int init();
int initWindow(int cmdShow);
int InitDevice();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LPDIRECT3D9 mDirect3D9;
LPD3DXSPRITE mSpriteHandler;
PDIRECT3D9 mD3d;
LPDIRECT3DDEVICE9 mDevice;
HINSTANCE mHInstance;
int mCmdShow;

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
//{
//    mHInstance = hInstance;
//    initWindow(cmdShow);
//    return 0;
//}

int main(int argc, char* argv[])
{
	init();
	return 0;
}

int init()
{

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = mHInstance;

	wc.lpfnWndProc = WNDPROC(WndProc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = nullptr;

	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = HBRUSH(GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = WIN_NAME;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	//WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
	const auto hWnd = CreateWindow(
		WIN_NAME,
		WIN_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameGlobal::getWidth(),
		GameGlobal::getHeight(),
		NULL,
		NULL,
		mHInstance,
		NULL);

	GameGlobal::setCurrentHINSTANCE(mHInstance);
	GameGlobal::setCurrentHWND(hWnd);

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	if (InitDevice())
	{
		Game game(FPS);
	}

	return 0;
}

int initWindow(int cmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = mHInstance;

	wc.lpfnWndProc = WNDPROC(WndProc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = nullptr;

	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = HBRUSH(GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = WIN_NAME;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	//WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
	const auto hWnd = CreateWindow(
		WIN_NAME,
		WIN_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameGlobal::getWidth(),
		GameGlobal::getHeight(),
		NULL,
		NULL,
		mHInstance,
		NULL);

	GameGlobal::setCurrentHINSTANCE(mHInstance);
	GameGlobal::setCurrentHWND(hWnd);

	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);

	if (InitDevice())
	{
		Game game(FPS);
	}

	return 0;
}

int InitDevice()
{
	mD3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = GameGlobal::getWidth();
	d3dpp.BackBufferHeight = GameGlobal::getHeight();

	const auto result = mD3d->CreateDevice(D3DADAPTER_DEFAULT,
	                                       D3DDEVTYPE_HAL,
	                                       GameGlobal::getCurrentHWND(),
	                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	                                       &d3dpp,
	                                       &mDevice);
	if (FAILED(result))
		return 0;

	GameGlobal::setCurrentDevice(mDevice);

	D3DXCreateSprite(GameGlobal::getCurrentDevice(), &mSpriteHandler);
	GameGlobal::setCurrentSpriteHandler(mSpriteHandler);

	return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
	su dung cac event cua window
	*/
	switch (message)
	{
	case WM_DESTROY:
		GameGlobal::isGameRunning = false;
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		SceneManager::getInstance()->getCurrentScene()->onMouseDown(float(GET_X_LPARAM(lParam)),
		                                                            float(GET_Y_LPARAM(lParam)));
		break;

	case WM_KEYDOWN:
		SceneManager::getInstance()->getCurrentScene()->onKeyDown(wParam);
		break;

	case WM_KEYUP:
		SceneManager::getInstance()->getCurrentScene()->onKeyUp(wParam);
		break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
