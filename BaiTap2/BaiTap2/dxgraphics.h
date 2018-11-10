#ifndef _DX_GRAPHICS_H
#define _DX_GRAPHICS_H

#include <d3d9.h>
#include <d3dx9.h>

class Graphics {

	LPDIRECT3D9 _d3d;

	LPDIRECT3DDEVICE9 _d3ddev;

	LPDIRECT3DSURFACE9 _backBuffer;

public:
	Graphics();
	~Graphics();

	bool Init_DirectX3D(HWND hWnd, int width, int height, int fullscreen);


	LPDIRECT3D9 getDirect3D();

	LPDIRECT3DDEVICE9 getDirect3DDevice();

	LPDIRECT3DSURFACE9 getBackBuffer();

	LPDIRECT3DSURFACE9 LoadSurFaces(const char* fileName, D3DCOLOR tranColor);

	LPDIRECT3DTEXTURE9 LoadTexture(const char* fileName, D3DCOLOR tranColor);

};

#endif
