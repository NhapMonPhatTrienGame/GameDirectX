#pragma once
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"

class Camera;

class PlayerBullet :public Entity
{
public:
	enum BulletType
	{
		Normal,
		BurstNormal,
		FirstLevel,
		BurstFirstLevel,
		SecondLevel,
		BurstSecondLevel
	};

	enum BulletState
	{
		Fire,
		Burst
	};

	PlayerBullet(BulletState state, BulletType type);
	~PlayerBullet();

	bool getBurst() const					{ return isBurst; }
	void setBulletX(float bulletX)			{ this->bulletX = bulletX; }

	bool getCurrentFlip() const				{ return currentFlip; }
	void setCurrentFlip(bool flag)			{ currentFlip = flag; }

	void changeBullet(BulletState state, BulletType type);

	RECT getBound() override;

	void drawSprite(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void update(float dt) override;
	void onCollision(SideCollisions side) override;
	void onCollision(Entity* obj) override;

protected:

	Animation*		pAnims;
	float			bulletX;
	bool			isBurst;

	BulletType		bulletType;
	BulletState		bulletState;

	bool			currentFlip;
};