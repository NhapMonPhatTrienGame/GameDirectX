#ifndef __ANIMATION__
#define __ANIMATION__

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"

using namespace std;

class Animation : public Sprite
{
protected:

	int				m_Rows, //so hang cua animation
					m_Columns,
					m_framePerRow, //so cot cua animation
					m_CurrentIndex, //gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
					m_CurrentRow, // hang hien tai
					m_FrameWidth, // chieu rong cua 1 frame 
					m_FrameHeight; // chieu dai cua 1 frame

	bool			m_LoopAnimation, 
					m_Shoot, 
					m_Pause;

	float			m_TimePerFrame, //thoi gian luan chuyen 1 frame
					m_CurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe

	RECT			m_Rect;

public:
	//ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight,
		float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	//void (int currentRow);
	//int GetCurrentRow();
	int getCurrentColumn() const;

	void setShoot(bool shoot);

	void setPause(bool pause);

	void setLoopAnimation(bool allowLoopAnimation);
	void setAnimation(int currentRow, int framePerRow, float timePerFrame = 0.1f, bool loopAnimation = true);

	virtual void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(),
		D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0,
		D3DXVECTOR2 rotationCenter = D3DXVECTOR2(),
		D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) override;

	void Draw(D3DXVECTOR2 translate);

	~Animation() = default;

};

#endif
