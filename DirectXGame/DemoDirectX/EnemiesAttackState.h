#pragma once
#include "EnemiesState.h"
#include "GameComponents/Sprite.h"

class EnemiesAttackState :
	public EnemiesState
{
	Sprite *pShooter;
public:
	explicit EnemiesAttackState(Enemies *e);
	~EnemiesAttackState();

	EnemyState::EnemyStateName getState() override;
};