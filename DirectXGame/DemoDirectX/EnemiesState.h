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
	virtual void OnCollision(Entity::SideCollisions t_Side);
	virtual void Update(float t_GameTime);
};

