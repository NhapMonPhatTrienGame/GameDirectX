#include "Sprite.h"
#include "GameGlobal.h"
#include "../GameDefines/GameDefine.h"

bool Sprite::_CheckRect(RECT SourceRect)
{
	if (SourceRect.left == SourceRect.right)
		return false;
	if (SourceRect.top == SourceRect.bottom)
		return false;
	return true;
}

Sprite::Sprite(const char* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
	_FlipX = false;
	_SpriteHandler = GameGlobal::GetCurrentSpriteHandler();
	_Position = D3DXVECTOR3(0, 0, 0);
	_Rotation = 0;
	_RotationCenter = D3DXVECTOR2(_Position.x, _Position.y);
	_Translation = D3DXVECTOR2(0, 0);
	_Scale = D3DXVECTOR2(1, 1);

	HRESULT result = D3DXGetImageInfoFromFile(filePath, &_ImageInfo);
	if (FAILED(result))
		return;

	if (width == 0)
	{
		if (!_CheckRect(sourceRect))
			_Width = _ImageInfo.Width;

		else
			_Width = sourceRect.right - sourceRect.left;
	}
	else _Width = width;

	if (height == 0)
	{
		if (!_CheckRect(sourceRect))
			_Height = _ImageInfo.Height;

		else
			_Height = sourceRect.bottom - sourceRect.top;
	}
	else _Height = height;

	if (!_CheckRect(sourceRect))
	{
		_SourceRect.left = 0;
		_SourceRect.right = _Width;
		_SourceRect.top = 0;
		_SourceRect.bottom = _Height;
	}

	LPDIRECT3DDEVICE9 device;
	_SpriteHandler->GetDevice(&device);

	result = D3DXCreateTextureFromFileEx(
		device,
		filePath,
		_ImageInfo.Width,
		_ImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&_ImageInfo,
		nullptr,
		&_Texture
	);
	if (FAILED(result))
		return;
}

Sprite::~Sprite()
{
	SAFE_RELEASE(_Texture);
}

void Sprite::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate, float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR Transcolor)
{
	auto inPosition = _Position;
	auto inSourceRect = _SourceRect;
	float inRotation = _Rotation;
	auto inScale = _Scale;
	auto inTranslation = _Translation;
	auto inRotationCenter = _RotationCenter;
	auto scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
	inRotation = Angle * (3.14159265358979323846 / 180);

	if (Position != D3DXVECTOR3())
		inPosition = Position;

	if (_CheckRect(SourceRect))
		inSourceRect = SourceRect;

	if (Scale != D3DXVECTOR2())
		inScale = Scale;

	if (Translate != D3DXVECTOR2())
		inTranslation = Translate;

	if (RotationCenter != D3DXVECTOR2())
		inRotationCenter = RotationCenter;
	else
		_RotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(
		&_Matrix,
		&scalingCenter,
		0,
		&inScale,
		&inRotationCenter,
		inRotation,
		&inTranslation
	);

	D3DXMATRIX oldMatrix;
	_SpriteHandler->GetTransform(&oldMatrix);
	_SpriteHandler->SetTransform(&_Matrix);

	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	_SpriteHandler->Draw(
		_Texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	_SpriteHandler->SetTransform(&oldMatrix);
}

void Sprite::SetSourceRect(RECT rect)
{
	_SourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture() const
{
	return _Texture;
}

D3DXVECTOR3 Sprite::GetPosition() const
{
	return _Position;
}
void Sprite::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR2(x, y));
}
void Sprite::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}
void Sprite::SetPosition(D3DXVECTOR3 pos)
{
	_Position = pos;
}

D3DXVECTOR2 Sprite::GetScale() const
{
	return _Scale;
}
void Sprite::SetScale(D3DXVECTOR2 scale)
{
	_Scale = scale;
}

D3DXVECTOR2 Sprite::GetTranslation() const
{
	return _Translation;
}
void Sprite::SetTranslation(D3DXVECTOR2 translation)
{
	_Translation = translation;
}

D3DXVECTOR2 Sprite::GetRotationCenter() const
{
	return _RotationCenter;
}
void Sprite::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
	_RotationCenter = rotationCenter;
}

float Sprite::GetRotation() const
{
	return _Rotation;
}
void Sprite::SetRotation(float rotation)
{
	_Rotation = rotation;
}

D3DXIMAGE_INFO Sprite::GetImageInfo() const
{
	return _ImageInfo;
}

void Sprite::SetFlip(bool flag)
{
	if (_FlipX != flag)
	{
		_FlipX = flag;
		_Scale = D3DXVECTOR2(-_Scale.x, _Scale.y);
	}
}

int Sprite::GetWidth() const
{
	return _Width;
}
void Sprite::SetWidth(int width)
{
	_Width = width;
}

int Sprite::GetHeight() const
{
	return _Height;
}
void Sprite::SetHeight(int height)
{
	_Height = height;
}