#pragma once
#include "EnemiesState.h"


class EnemiesStandState :
	public EnemiesState
{
	float m_TimeJump;
public:
	explicit EnemiesStandState(Enemies *e);
	~EnemiesStandState() = default;

	EnemyState::EnemyStateName getState() override;
	void Update(float t_GameTime) override;
};