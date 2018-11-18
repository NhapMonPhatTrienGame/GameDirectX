#pragma once
#include "GameObjects/Player/GameState/GameState.h"

class Enemies;

class EnemiesState
{
protected:
	Enemies *e;
public:
	explicit EnemiesState(Enemies *e);
	virtual ~EnemiesState() = default;

	virtual EnemyState::EnemyStateName getState() = 0;
	virtual void onCollision(Entity::SideCollisions side);
	virtual void update(float dt);
};

