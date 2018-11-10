#include "dxgraphics.h"

LPDIRECT3DSURFACE9 Graphics::LoadSurFaces(const char * fileName, D3DCOLOR tranColor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(fileName, &info);
	if (FAILED(result))
		return NULL;

	result = _d3ddev->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,
		NULL
	);
	if (FAILED(result))
		return NULL;

	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		fileName,
		NULL,
		D3DX_DEFAULT,
		tranColor,
		NULL
	);

	if (FAILED(result))
		return NULL;

	return image;

}

LPDIRECT3DTEXTURE9 Graphics::LoadTexture(const char * fileName, D3DCOLOR tranColor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO image_info;

	HRESULT result = D3DXGetImageInfoFromFile(fileName, &image_info);
	if (FAILED(result))
		return NULL;

	result = D3DXCreateTextureFromFileEx(_d3ddev, fileName, image_info.Width, image_info.Height, 1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, tranColor, &image_info, NULL, &texture);
	if (FAILED(result)) 
		return NULL;

	return texture;

}

Graphics::Graphics()
{
	_d3d = NULL;
	_d3ddev = NULL;
	_backBuffer = NULL;
}

Graphics::~Graphics()
{
	if (_d3d)
	{
		_d3d->Release();
		_d3d = NULL;
	}
	if (_d3ddev)
	{
		_d3ddev->Release();
		_d3ddev = NULL;
	}
}

bool Graphics::Init_DirectX3D(HWND hWnd, int width, int height, int fullscreen)
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!_d3d)
	{
		MessageBox(hWnd, "Error initializing Direct3D", "Error", MB_OK);
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = !fullscreen;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddev
	);

	if (!_d3ddev)
	{
		MessageBox(hWnd, "Error initializing Direct3D Device", "Error", MB_OK);
		return false;
	}

	//Clear the _backBuffer to black
	_d3ddev->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0
	);

	//Create the pointer to the _back buffer
	_d3ddev->GetBackBuffer(
		0,
		0,
		D3DBACKBUFFER_TYPE_MONO,
		&_backBuffer
	);

	return true;
}

LPDIRECT3D9 Graphics::getDirect3D()
{
	return _d3d;
}

LPDIRECT3DDEVICE9 Graphics::getDirect3DDevice()
{
	return _d3ddev;
}

LPDIRECT3DSURFACE9 Graphics::getBackBuffer()
{
	return _backBuffer;
}