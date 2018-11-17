#pragma once
#include "EnemiesState.h"


class EnemiesStandState :
	public EnemiesState
{
	float timeJump;
public:
	explicit EnemiesStandState(Enemies *e);
	~EnemiesStandState() = default;

	EnemyState::EnemyStateName getState() override;
	void update(float dt) override;
};