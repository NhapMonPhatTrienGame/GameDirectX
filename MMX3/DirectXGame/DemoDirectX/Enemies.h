#pragma once

#include "GameObjects/Entity/Entity.h"
#include "GameDefines/GameDefine.h"
#include "GameComponents/Animation.h"
#include "GameComponents/Camera.h"

class EnemiesState;

class Enemies :
	public Entity
{
protected:
	EnemiesState*					pState;
	Animation *pCurrentAnim;

	EnemyState::EnemyStateName		currentState;
	bool							currentFlip;
	bool							allowDrawSprite;	// allow to draw the sprite when the Camera contain Enemies

public:
	Enemies();
	~Enemies();

	void ChangeAnimation(EnemyState::EnemyStateName state);

	void setFlip(bool flip)				{ currentFlip = flip; }
	bool getFlip() const				{ return currentFlip; }

	void setDrawSprite(bool isDraw)		{ allowDrawSprite = isDraw; }
	bool getDrawSprite() const			{ return allowDrawSprite; }

	void setState(EnemiesState * newState);
	RECT getBound() override;

	void drawSprite(Camera*	pCamera,VECTOR3 pos = VECTOR3(), RECT rect = RECT(), VECTOR2 scale = VECTOR2(), VECTOR2 translate = VECTOR2(), float angle = 0, VECTOR2 rotationCenter = VECTOR2(), DX_COLOR transColor = D3DCOLOR_XRGB(255, 255, 255));

	void update(float gameTime) override;
	void onCollision(SideCollisions side) override;
	void onCollisionBottom();
};