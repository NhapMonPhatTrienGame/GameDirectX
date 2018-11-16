#pragma once
#include "EnemiesState.h"
#include "GameComponents/Sprite.h"

class EnemiesAttackState :
	public EnemiesState
{
	Sprite *m_Shooter;
public:
	explicit EnemiesAttackState(Enemies *e);
	~EnemiesAttackState();

	EnemyState::EnemyStateName getState() override;
};