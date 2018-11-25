#pragma once
#include "../EnemiesState.h"

class EnemiesJumpState :
	public EnemiesState
{
public:
	explicit EnemiesJumpState(Enemies *e);
	~EnemiesJumpState() = default;

	void onCollision(Entity::SideCollisions side) override;
	void update(float dt) override;
	Enemies::StateName getState() override;

protected:
	float translateY;

};
