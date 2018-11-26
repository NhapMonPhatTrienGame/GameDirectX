#pragma once
#include "../EnemiesState.h"

class EnemiesFallState
	:public EnemiesState
{
public:
	explicit EnemiesFallState(Enemies* e);
	~EnemiesFallState() override = default;

	void onCollision(Entity::SideCollisions side) override;
	void update(float dt) override;
	Enemies::StateName getState() override;

protected:
	float translateY;
};
