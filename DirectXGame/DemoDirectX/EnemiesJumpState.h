#pragma once
#include "EnemiesState.h"

class EnemiesJumpState :
	public EnemiesState
{
	float m_TranslateY;
	float m_TimeJump;

public:
	explicit EnemiesJumpState(Enemies *e);
	~EnemiesJumpState() = default;

	EnemyState::EnemyStateName getState() override;
	void OnCollision(Entity::SideCollisions t_Side) override;
	void Update(float t_GameTime) override;
};