#pragma once
#include "EnemiesState.h"

class EnemiesJumpState :
	public EnemiesState
{
	float translateY;

public:
	explicit EnemiesJumpState(Enemies *e);
	~EnemiesJumpState() = default;

	EnemyState::EnemyStateName getState() override;
	void onCollision(Entity::SideCollisions side) override;
	void update(float dt) override;
};