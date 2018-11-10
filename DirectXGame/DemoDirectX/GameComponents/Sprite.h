#ifndef __SPRITE__
#define __SPRITE__
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
protected:

	D3DXVECTOR3             _Position;				//Position of the sprite is located in the middle of texture image
	LPDIRECT3DTEXTURE9      _Texture;				//Image will be saved here
	LPD3DXSPRITE            _SpriteHandler;			//SpriteHandler: Image drawing support
	D3DXIMAGE_INFO          _ImageInfo;				//The actual information of the image is taken
	RECT                    _SourceRect;			//Rectangle is cut from the texture image

	int                     _Width, _Height;		//Size of texture image

	float                   _Rotation;				//The spin angle of the sprite is calculated in radians

	D3DXVECTOR2             _Scale;					// Vector custom zoom in or zoom out of texture
	D3DXVECTOR2             _Translation;			//Image is translated from the sprite + mTranslate
	D3DXMATRIX              _Matrix;				//Matrix of the sprite support for geometry
	D3DXVECTOR2             _RotationCenter;		// (origin vector)

	bool					_FlipX;
	static bool _CheckRect(RECT SourceRect);
public:

	explicit Sprite(const char* filePath, RECT sourceRect = RECT(), int width = 0, int height = 0,
		D3DCOLOR colorKey = NULL);

	Sprite() = default;

	virtual ~Sprite();

	LPDIRECT3DTEXTURE9 GetTexture() const;

	virtual void Draw(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(),
		D3DXVECTOR2 Scale = D3DXVECTOR2(), D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0,
		D3DXVECTOR2 RotationCenter = D3DXVECTOR2(), D3DXCOLOR Transcolor = D3DCOLOR_XRGB(255, 255, 255));
	
	void SetWidth(int width);
	int GetWidth() const;

	void SetHeight(int height);
	int GetHeight() const;

	// Get information about an image
	D3DXIMAGE_INFO GetImageInfo() const;

	D3DXVECTOR3 GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 pos);
	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR2 GetScale() const;
	void SetScale(D3DXVECTOR2 scale);

	//The translation from the position of the World to the position of the View
	D3DXVECTOR2 GetTranslation() const;
	void SetTranslation(D3DXVECTOR2 translation);

	D3DXVECTOR2 GetRotationCenter() const;
	void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	//Rotate by radian
	float GetRotation() const;
	void SetRotation(float rotation);

	void SetSourceRect(RECT rect);

	//True: Flip horizontally
	//False: Don't flip
	void SetFlip(bool flag);
};

#endif