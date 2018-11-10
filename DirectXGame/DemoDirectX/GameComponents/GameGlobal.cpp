#include "GameGlobal.h"

HINSTANCE GameGlobal::mHINSTANCE = NULL;
HWND GameGlobal::mHWND = NULL;
LPD3DXSPRITE GameGlobal::mSpriteHandler = NULL;
int GameGlobal::mWidth = 600;
int GameGlobal::mHeight = 600;
LPDIRECT3DDEVICE9 GameGlobal::mDevice = nullptr;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = nullptr;


void GameGlobal::SetCurrentDevice(LPDIRECT3DDEVICE9 device)
{
    mDevice = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetCurrentDevice()
{
    return mDevice;
}


HINSTANCE GameGlobal::GetCurrentHINSTANCE()
{
    return mHINSTANCE;
}

HWND GameGlobal::getCurrentHWND()
{
    return mHWND;
}

void GameGlobal::SetCurrentHINSTANCE(HINSTANCE hInstance)
{
    mHINSTANCE = hInstance;
}

void GameGlobal::SetCurrentHWND(HWND hWnd)
{
    mHWND = hWnd;
}

void GameGlobal::SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
    mSpriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetCurrentSpriteHandler()
{
    return mSpriteHandler;
}

void GameGlobal::SetWidth(int width)
{
    mWidth = width;
}

int GameGlobal::GetWidth()
{
    return mWidth;
}

void GameGlobal::SetHeight(int height)
{
    mHeight = height;
}

int GameGlobal::GetHeight()
{
    return mHeight;
}