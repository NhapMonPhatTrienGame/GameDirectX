#pragma once
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"

class Camera;

class EnemiesBullet :
	public Entity
{
public:
	EnemiesBullet();
	~EnemiesBullet();

	RECT getBound() override;

	bool getBurst() const { return isBurst; }

	void drawSprite(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void update(float dt) override;
	void onCollision(SideCollisions side) override;
	void onCollision(Entity* obj) override;

protected:

	Animation*			pAnim;
	float				bulletY;	// The bullet translate to y axis
	bool				isBurst;	//nổ
};