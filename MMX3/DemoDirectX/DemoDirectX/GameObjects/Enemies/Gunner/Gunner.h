
#ifndef _INTRO_ENEMIES_H
#define _INTRO_ENEMIES_H

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "GunnerBullet/GunnerBullet.h"

class GunnerState;

enum class StateGunner
{
	Stand,
	Attack,
	AttackRocket,
	AttackBullet,
	Fall,
	Die,
	None
};

class Gunner :public Entity
{
protected:
	Animation*						anim;
	GunnerState*					pGunnerState;

	StateGunner						currentState;
	std::vector<GunnerBullet*>		listGunnerBullet;
	int								HP;

public:

	Gunner();
	~Gunner();

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(SidesCollision side) override;
	void onCollision(Entity* obj) override;
	void onNoCollisionWithBottom() override;

	void draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(100, 100, 100));
	void changeAnimation(StateGunner stateName);
	void setState(GunnerState *state);

	std::vector<GunnerBullet*> *getGunnerBullet()		{ return &listGunnerBullet; }
	StateGunner getStateName() const						{ return currentState; }

};

#endif
