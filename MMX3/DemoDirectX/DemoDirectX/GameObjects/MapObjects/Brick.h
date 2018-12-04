#pragma once

#include "../Entity/Entity.h"
#include "../../GameComponents/Animation.h"

//vien gach
class Brick : public Entity
{

public:
	Brick() = default;
	virtual ~Brick();

	void update(float dt) override;
	void drawSprite(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255)) const;
	void drawSprite(D3DXVECTOR2 transform) const;

protected:

	bool Init(D3DXVECTOR3 position);

	void onSetPosition(D3DXVECTOR3 pos) override;

	virtual const char* fileName() = 0;
	virtual int totalFrame() = 0;				// Total frame
	virtual int row() = 0;						//Number of resource animation row 
	virtual int column() = 0;					//Number of resource animation column
	virtual float timePerFrame() = 0;			//Number of seconds to transform animation

	Animation* pBrickAnimation;

};
