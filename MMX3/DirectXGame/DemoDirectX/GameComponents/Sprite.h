#ifndef __SPRITE__
#define __SPRITE__
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
public:
	explicit Sprite(const char* filePath, RECT sourceRect = RECT(), int width = 0, int height = 0,
		D3DCOLOR colorKey = NULL);
	virtual ~Sprite();

	LPDIRECT3DTEXTURE9 getTexture() const;

	virtual void drawSprite(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(),
		D3DXVECTOR2 Scale = D3DXVECTOR2(), D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0,
		D3DXVECTOR2 RotationCenter = D3DXVECTOR2(), D3DXCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255));

	void setWidth(int width);
	int getWidth() const;

	void setHeight(int height);
	int getHeight() const;

	// Get information about an image
	D3DXIMAGE_INFO getImageInfo() const;

	D3DXVECTOR3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(D3DXVECTOR2 pos);
	void setPosition(D3DXVECTOR3 pos);

	D3DXVECTOR2 getScale() const;
	void setScale(D3DXVECTOR2 scale);

	//The translation from the position of the World to the position of the View
	D3DXVECTOR2 getTranslation() const;
	void setTranslation(D3DXVECTOR2 translation);

	D3DXVECTOR2 getRotationCenter() const;
	void setRotationCenter(D3DXVECTOR2 rotationCenter);

	//Rotate by radian
	float getRotation() const;
	void setRotation(float rotation);

	void setSourceRect(RECT rect);

	//True: Flip horizontally
	//False: Don't flip
	void setFlip(bool flag);

protected:

	D3DXVECTOR3						position; //Position of the sprite is located in the middle of texture image
	LPDIRECT3DTEXTURE9				texture; //Image will be saved here
	LPD3DXSPRITE					spriteHandler; //SpriteHandler: Image drawing support
	D3DXIMAGE_INFO					imageInfo; //The actual information of the image is taken
	RECT							sourceRect; //Rectangle is cut from the texture image

	int								width,
									height; //Size of texture image

	float							rotation; //The spin angle of the sprite is calculated in radians

	D3DXVECTOR2						scale; // Vector custom zoom in or zoom out of texture
	D3DXVECTOR2						translation; //Image is translated from the sprite + mTranslate
	D3DXMATRIX						matrix; //Matrix of the sprite support for geometry
	D3DXVECTOR2						rotationCenter; // (origin vector)

	bool							isFlipX;

	static bool isCheckRect(RECT SourceRect);
};

#endif