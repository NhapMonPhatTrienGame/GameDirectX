#include "Sprite.h"
#include "GameGlobal.h"
#include "../GameDefines/GameDefine.h"

bool Sprite::isCheckRect(RECT SourceRect)
{
	if (SourceRect.left == SourceRect.right)
		return false;
	if (SourceRect.top == SourceRect.bottom)
		return false;
	return true;
}

Sprite::Sprite(const char* filePath, RECT sourceRect, int width, int height, D3DCOLOR colorKey)
{
	isFlipX = false;
	spriteHandler = GameGlobal::getCurrentSpriteHandler();
	position = D3DXVECTOR3(0, 0, 0);
	rotation = 0;
	rotationCenter = D3DXVECTOR2(position.x, position.y);
	translation = D3DXVECTOR2(0, 0);
	scale = D3DXVECTOR2(1, 1);

	auto result = D3DXGetImageInfoFromFile(filePath, &imageInfo);
	if (FAILED(result))
		return;

	if (width == 0)
	{
		if (!isCheckRect(sourceRect))
			this->width = imageInfo.Width;
		else
			this->width = sourceRect.right - sourceRect.left;
	}
	else 
		this->width = width;

	if (height == 0)
	{
		if (!isCheckRect(sourceRect))
			this->height = imageInfo.Height;
		else
			this->height = sourceRect.bottom - sourceRect.top;
	}
	else 
		this->height = height;

	if (!isCheckRect(sourceRect))
	{
		this->sourceRect.left = 0;
		this->sourceRect.right = this->width;
		this->sourceRect.top = 0;
		this->sourceRect.bottom = this->height;
	}

	LPDIRECT3DDEVICE9 device;
	spriteHandler->GetDevice(&device);

	result = D3DXCreateTextureFromFileEx(
		device,
		filePath,
		imageInfo.Width,
		imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&imageInfo,
		nullptr,
		&texture
	);
	if (FAILED(result))
		return;
}

Sprite::~Sprite()
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(spriteHandler);
}

void Sprite::drawSprite(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate,
	float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR transColor)
{
	auto inPosition = position;
	auto inSourceRect = sourceRect;
	auto inRotation = rotation;
	auto inScale = scale;
	auto inTranslation = translation;
	auto inRotationCenter = rotationCenter;
	auto scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
	inRotation = Angle * (3.14159265358979323846 / 180);

	if (Position != D3DXVECTOR3())
		inPosition = Position;

	if (isCheckRect(SourceRect))
		inSourceRect = SourceRect;

	if (Scale != D3DXVECTOR2())
		inScale = Scale;

	if (Translate != D3DXVECTOR2())
		inTranslation = Translate;

	if (RotationCenter != D3DXVECTOR2())
		inRotationCenter = RotationCenter;
	else
		rotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(
		&matrix,
		&scalingCenter,
		0,
		&inScale,
		&inRotationCenter,
		inRotation,
		&inTranslation
	);

	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);

	D3DXVECTOR3 center(float(width) / 2, float(height) / 2, 0);

	spriteHandler->Draw(
		texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	spriteHandler->SetTransform(&oldMatrix);
}

void Sprite::setSourceRect(RECT rect)
{
	sourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::getTexture() const
{
	return texture;
}

D3DXVECTOR3 Sprite::getPosition() const
{
	return position;
}

void Sprite::setPosition(float x, float y)
{
	setPosition(D3DXVECTOR2(x, y));
}

void Sprite::setPosition(D3DXVECTOR2 pos)
{
	setPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Sprite::setPosition(D3DXVECTOR3 pos)
{
	position = pos;
}

D3DXVECTOR2 Sprite::getScale() const
{
	return scale;
}

void Sprite::setScale(D3DXVECTOR2 scale)
{
	this->scale = scale;
}

D3DXVECTOR2 Sprite::getTranslation() const
{
	return translation;
}

void Sprite::setTranslation(D3DXVECTOR2 translation)
{
	this->translation = translation;
}

D3DXVECTOR2 Sprite::getRotationCenter() const
{
	return rotationCenter;
}

void Sprite::setRotationCenter(D3DXVECTOR2 rotationCenter)
{
	this->rotationCenter = rotationCenter;
}

float Sprite::getRotation() const
{
	return rotation;
}

void Sprite::setRotation(float rotation)
{
	this->rotation = rotation;
}

D3DXIMAGE_INFO Sprite::getImageInfo() const
{
	return imageInfo;
}

void Sprite::setFlip(bool flag)
{
	if (isFlipX != flag)
	{
		isFlipX = flag;
		scale = D3DXVECTOR2(-scale.x, scale.y);
	}
}

int Sprite::getWidth() const
{
	return width;
}

void Sprite::setWidth(int width)
{
	this->width = width;
}

int Sprite::getHeight() const
{
	return height;
}

void Sprite::setHeight(int height)
{
	this->height = height;
}