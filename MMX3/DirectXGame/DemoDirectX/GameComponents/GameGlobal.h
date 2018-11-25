#ifndef __GAME_GLOBAL_H__
#define __GAME_GLOBAL_H__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class GameGlobal
{
public:
	static HINSTANCE getCurrentHINSTANCE();
	static HWND getCurrentHWND();

	static void setCurrentHINSTANCE(HINSTANCE hInstance);
	static void setCurrentHWND(HWND hWnd);

	static void setCurrentSpriteHandler(LPD3DXSPRITE spriteHandler);
	static LPD3DXSPRITE getCurrentSpriteHandler();

	static void setCurrentDevice(LPDIRECT3DDEVICE9 device);
	static LPDIRECT3DDEVICE9 getCurrentDevice();

	static void setWidth(int width);
	static int getWidth();

	static void setHeight(int height);
	static int getHeight();

	static LPDIRECT3DSURFACE9 backSurface;

	static bool isGameRunning; //Game State 

private:
	static HINSTANCE hInstance; //current Windows HINSTANCE
	static HWND hWnd; //current HWND
	static LPD3DXSPRITE spriteHandler; //Current SpriteHandler
	static int width, height; //Size of windows
	static LPDIRECT3DDEVICE9 d3ddv; //Current direct device
};

#endif
