
#ifndef __GAME_GLOBAL_H__
#define __GAME_GLOBAL_H__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class GameGlobal
{
	static HINSTANCE mHINSTANCE;			//current Windows HINSTANCE
	static HWND mHWND;						//current HWND
	static LPD3DXSPRITE mSpriteHandler;		//Current SpriteHandler
	static int mWidth, mHeight;				//Size of windows
	static LPDIRECT3DDEVICE9 mDevice;		//Current direct device

public:
    GameGlobal() = default;
    ~GameGlobal() = default;

    static HINSTANCE GetCurrentHINSTANCE();
    static HWND getCurrentHWND();

    static void SetCurrentHINSTANCE(HINSTANCE hInstance);
    static void SetCurrentHWND(HWND hWnd);

    static void SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler);
    static LPD3DXSPRITE GetCurrentSpriteHandler();

    static void SetCurrentDevice(LPDIRECT3DDEVICE9 device);
    static LPDIRECT3DDEVICE9 GetCurrentDevice();

    static void SetWidth(int width);
    static int GetWidth();

    static void SetHeight(int height);
    static int GetHeight();

    static LPDIRECT3DSURFACE9 backSurface;

    static bool isGameRunning; //Game State 

};

#endif

