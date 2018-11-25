#pragma once
#include "../../Entity/Entity.h"
#include "../Enemies.h"

class Enemies;

class EnemiesState
{

public:
	explicit EnemiesState(Enemies *e);
	virtual ~EnemiesState() = default;

	virtual Enemies::StateName getState() = 0;
	virtual void onCollision(Entity::SideCollisions side);
	virtual void update(float dt);

protected:
	Enemies *e;

};