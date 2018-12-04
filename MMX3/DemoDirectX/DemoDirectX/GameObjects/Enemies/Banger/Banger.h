#pragma once

#include <vector>
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "BangerBullet/BangerBullet.h"

class BangerState;

enum class StateBanger
{
	Stand,
	Jump,
	Fall,
	Attack,
	Die,
	None
};

class Banger :
	public Entity
{
protected:
	BangerState*						pState;
	Animation*							pCurrentAnim;
	Animation*							pAnimationDie;

	std::vector<BangerBullet*>			ListBullet;
	StateBanger							currentState;
	int									HP;


public:

	Banger();
	~Banger();

	void changeAnimation(StateBanger state);

	Animation* getAnim() const							{ return pCurrentAnim; }
	std::vector<BangerBullet*> *getBangerBullet()		{ return &ListBullet; }

	void setState(BangerState * newState);
	RECT getBound() override;

	void draw(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0.0f, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR transColor = D3DCOLOR_XRGB(255,255,255));
	void update(float gameTime) override;
	void onCollision(SidesCollision side) override;
	void onCollision(Entity* obj) override;
	void onNoCollisionWithBottom() override;

};