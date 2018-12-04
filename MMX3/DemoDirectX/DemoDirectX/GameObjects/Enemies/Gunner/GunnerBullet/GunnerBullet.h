#ifndef _HEAD_GUNNER_BULLET_H
#define _HEAD_GUNNER_BULLET_H
#include "../../../Entity/Entity.h"
#include "../../../../GameComponents/Animation.h"

class Camera;

enum class BulletState
{
	Fire,
	Burst
};

class GunnerBullet :public Entity
{
protected:
	virtual void changeState(BulletState state);

	Animation*		anim;
	Animation*		animBurst;
	bool			isBurst;
	float			bulletX,
					timeFire;
	BulletState		bulletState;

public:

	GunnerBullet();
	~GunnerBullet();
	RECT getBound() override;

	virtual void newBullet(float bx, float by, bool direction);
	void update(float dt) override;
	void onCollision(SidesCollision side) override;
	void onCollision(Entity* obj) override;

	virtual void draw(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	
	void setBulletX(float bulletX)		{ this->bulletX = bulletX; }
	virtual bool getBurst() const		{ return isBurst; }

};

#endif
