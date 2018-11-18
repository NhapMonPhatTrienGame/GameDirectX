#include "GameGlobal.h"

HINSTANCE GameGlobal::hInstance = nullptr;
HWND GameGlobal::hWnd = nullptr;
LPD3DXSPRITE GameGlobal::spriteHandler = nullptr;
int GameGlobal::width = 600;
int GameGlobal::height = 600;
LPDIRECT3DDEVICE9 GameGlobal::d3ddv = nullptr;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = nullptr;


void GameGlobal::setCurrentDevice(LPDIRECT3DDEVICE9 device)
{
	d3ddv = device;
}
LPDIRECT3DDEVICE9 GameGlobal::getCurrentDevice()
{
	return d3ddv;
}


HINSTANCE GameGlobal::getCurrentHINSTANCE()
{
	return hInstance;
}
HWND GameGlobal::getCurrentHWND()
{
	return hWnd;
}

void GameGlobal::setCurrentHINSTANCE(HINSTANCE hInstance)
{
	GameGlobal::hInstance = hInstance;
}
void GameGlobal::setCurrentHWND(HWND hWnd)
{
	GameGlobal::hWnd = hWnd;
}

void GameGlobal::setCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	GameGlobal::spriteHandler = spriteHandler;
}
LPD3DXSPRITE GameGlobal::getCurrentSpriteHandler()
{
	return spriteHandler;
}

void GameGlobal::setWidth(int width)
{
	GameGlobal::width = width;
}
int GameGlobal::getWidth()
{
	return width;
}

void GameGlobal::setHeight(int height)
{
	GameGlobal::height = height;
}
int GameGlobal::getHeight()
{
	return height;
}
