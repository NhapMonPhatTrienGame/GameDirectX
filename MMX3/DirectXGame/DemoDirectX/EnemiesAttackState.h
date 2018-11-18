#pragma once
#include "EnemiesState.h"
#include "GameComponents/Sprite.h"

class EnemiesAttackState :
	public EnemiesState
{
	Sprite *pShooter;
	float timeAttack;
public:
	explicit EnemiesAttackState(Enemies *e);
	~EnemiesAttackState();

	EnemyState::EnemyStateName getState() override;
	void update(float dt) override;
};