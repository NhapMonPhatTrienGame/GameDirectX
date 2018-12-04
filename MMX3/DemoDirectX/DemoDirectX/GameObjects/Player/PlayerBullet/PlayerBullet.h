#pragma once
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"

class Camera;

enum class BulletType
{
	Normal,
	BurstNormal,
	FirstLevel,
	BurstFirstLevel,
	SecondLevel,
	BurstSecondLevel
};

enum class PlayerBulletState
{
	Fire,
	Burst
};

class PlayerBullet :public Entity
{
protected:

	Animation*		pAnims;
	float			bulletX;
	bool			isBurst;

	BulletType		bulletType;
	PlayerBulletState		bulletState;

public:

	PlayerBullet(PlayerBulletState state, BulletType type);
	~PlayerBullet();

	bool getBurst() const					{ return isBurst; }
	void setBulletX(float bulletX)			{ this->bulletX = bulletX; }

	void changeBullet(PlayerBulletState state, BulletType type);

	RECT getBound() override;

	void draw(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void update(float dt) override;
	void onCollision(SidesCollision side) override;
	void onCollision(Entity* obj) override;
};