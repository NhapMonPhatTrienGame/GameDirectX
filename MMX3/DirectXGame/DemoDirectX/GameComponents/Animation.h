#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"

using namespace std;

class Animation : public Sprite
{
public:
	//ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight,
		float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	int getCurrentColumn() const						{ return currentIndex; }
	void setShoot(bool shoot)							{ this->isShoot = shoot; }
	void setPause(bool pause)							{ this->isPause = pause; }
	bool getPause() const								{ return this->isPause; }
	void setLoopAnimation(bool allowLoopAnimation)		{ this->isLoopAnimation = allowLoopAnimation; }

	void setFrames(int frameW, int frameH);

	void setAnimation(int currentRow, int framePerRow, float timePerFrame = 0.1f, bool loopAnimation = true);

	void update(float dt);

	void drawSprite(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(),
		D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, 
		D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;

	void drawSprite(D3DXVECTOR2 translate);

protected:

	int				row,				//so hang cua animation
					cols,
					framePerRow,		//so cot cua animation
					currentIndex,		//gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
					currentRow,			// hang hien tai
					frameWidth,			// chieu rong cua 1 frame 
					frameHeight;		// chieu dai cua 1 frame

	bool			isLoopAnimation,
					isShoot,
					isPause;

	float			timePerFrame,		//thoi gian luan chuyen 1 frame
					currentTotalTime;	//tong thoi gian hien tai de thuc hien timeperframe

	RECT			rect;

};
#endif