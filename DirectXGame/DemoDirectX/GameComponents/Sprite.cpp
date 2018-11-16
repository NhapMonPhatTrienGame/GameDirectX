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
	m_FlipX = false;
	m_SpriteHandler = GameGlobal::GetCurrentSpriteHandler();
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Rotation = 0;
	m_RotationCenter = D3DXVECTOR2(m_Position.x, m_Position.y);
	m_Translation = D3DXVECTOR2(0, 0);
	m_Scale = D3DXVECTOR2(1, 1);

	HRESULT result = D3DXGetImageInfoFromFile(filePath, &m_ImageInfo);
	if (FAILED(result))
		return;

	if (width == 0)
	{
		if (!isCheckRect(sourceRect))
			m_Width = m_ImageInfo.Width;

		else
			m_Width = sourceRect.right - sourceRect.left;
	}
	else m_Width = width;

	if (height == 0)
	{
		if (!isCheckRect(sourceRect))
			m_Height = m_ImageInfo.Height;

		else
			m_Height = sourceRect.bottom - sourceRect.top;
	}
	else m_Height = height;

	if (!isCheckRect(sourceRect))
	{
		m_SourceRect.left = 0;
		m_SourceRect.right = m_Width;
		m_SourceRect.top = 0;
		m_SourceRect.bottom = m_Height;
	}

	LPDIRECT3DDEVICE9 device;
	m_SpriteHandler->GetDevice(&device);

	result = D3DXCreateTextureFromFileEx(
		device,
		filePath,
		m_ImageInfo.Width,
		m_ImageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&m_ImageInfo,
		nullptr,
		&m_Texture
	);
	if (FAILED(result))
		return;
}

Sprite::~Sprite()
{
	SAFE_RELEASE(m_Texture);
	SAFE_RELEASE(m_SpriteHandler);
}

void Sprite::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate, float Angle,
	D3DXVECTOR2 RotationCenter, D3DXCOLOR Transcolor)
{
	auto inPosition = m_Position;
	auto inSourceRect = m_SourceRect;
	float inRotation = m_Rotation;
	auto inScale = m_Scale;
	auto inTranslation = m_Translation;
	auto inRotationCenter = m_RotationCenter;
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
		m_RotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(
		&m_Matrix,
		&scalingCenter,
		0,
		&inScale,
		&inRotationCenter,
		inRotation,
		&inTranslation
	);

	D3DXMATRIX oldMatrix;
	m_SpriteHandler->GetTransform(&oldMatrix);
	m_SpriteHandler->SetTransform(&m_Matrix);

	D3DXVECTOR3 center((float)m_Width / 2, (float)m_Height / 2, 0);

	m_SpriteHandler->Draw(
		m_Texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	m_SpriteHandler->SetTransform(&oldMatrix);
}

void Sprite::setSourceRect(RECT rect)
{
	m_SourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::getTexture() const
{
	return m_Texture;
}

D3DXVECTOR3 Sprite::getPosition() const
{
	return m_Position;
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
	m_Position = pos;
}

D3DXVECTOR2 Sprite::getScale() const
{
	return m_Scale;
}

void Sprite::setScale(D3DXVECTOR2 scale)
{
	m_Scale = scale;
}

D3DXVECTOR2 Sprite::getTranslation() const
{
	return m_Translation;
}

void Sprite::setTranslation(D3DXVECTOR2 translation)
{
	m_Translation = translation;
}

D3DXVECTOR2 Sprite::getRotationCenter() const
{
	return m_RotationCenter;
}

void Sprite::setRotationCenter(D3DXVECTOR2 rotationCenter)
{
	m_RotationCenter = rotationCenter;
}

float Sprite::getRotation() const
{
	return m_Rotation;
}

void Sprite::setRotation(float rotation)
{
	m_Rotation = rotation;
}

D3DXIMAGE_INFO Sprite::getImageInfo() const
{
	return m_ImageInfo;
}

void Sprite::setFlip(bool flag)
{
	if (m_FlipX != flag)
	{
		m_FlipX = flag;
		m_Scale = D3DXVECTOR2(-m_Scale.x, m_Scale.y);
	}
}

int Sprite::getWidth() const
{
	return m_Width;
}

void Sprite::setWidth(int width)
{
	m_Width = width;
}

int Sprite::getHeight() const
{
	return m_Height;
}

void Sprite::setHeight(int height)
{
	m_Height = height;
}
