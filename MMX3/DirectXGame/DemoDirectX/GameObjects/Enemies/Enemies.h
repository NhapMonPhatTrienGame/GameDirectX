#pragma once

#include <vector>
#include "../Entity/Entity.h"
#include "../../GameComponents/Animation.h"
#include "EnemiesBullet/EnemiesBullet.h"

class EnemiesState;

class Enemies :
	public Entity
{

public:

	Enemies();
	~Enemies();

	enum StateName
	{
		Stand,
		Jump,
		Fall,
		Attack,
		Die
	};

	void changeAnimation(StateName state);

	Animation* getAnim() const						{ return pCurrentAnim; }
	std::vector<EnemiesBullet*> *getBullet()		{ return &ListBullet; }

	void setFlip(bool flip)							{ currentFlip = flip; }
	bool getFlip() const							{ return currentFlip; }

	void setState(EnemiesState * newState);
	RECT getBound() override;

	void drawSprite(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0.0f, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR transColor = D3DCOLOR_XRGB(255,255,255));
	void update(float gameTime) override;
	void onCollision(SideCollisions side) override;
	void onNoCollisionWithBottom() override;

protected:
	EnemiesState*					pState;
	Animation*						pCurrentAnim;

	bool							currentFlip;
	std::vector<EnemiesBullet*>		ListBullet;
	StateName						currentState;
};
