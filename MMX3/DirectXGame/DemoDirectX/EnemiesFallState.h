#pragma once
#include "EnemiesState.h"

class EnemiesFallState
	:public EnemiesState
{
	float translateY;
public:
	explicit EnemiesFallState(Enemies* e);

	~EnemiesFallState() override = default;

	EnemyState::EnemyStateName getState() override;
	void onCollision(Entity::SideCollisions side) override;
	void update(float dt) override;
};
