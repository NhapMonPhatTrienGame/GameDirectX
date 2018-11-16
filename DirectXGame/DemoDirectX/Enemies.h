#pragma once

#include "GameObjects/Entity/Entity.h"
#include "GameDefines/GameDefine.h"
#include "GameComponents/Animation.h"

class EnemiesState;

class Enemies :
	public Entity
{
protected:
	EnemiesState*					m_State;

	Animation*						m_Animation[3];
	Animation*						m_CurrentAnimation;

	EnemyState::EnemyStateName		m_CurrentState;
	bool							m_CurrentFlip;

public:
	Enemies();
	~Enemies();

	void ChangeAnimation(EnemyState::EnemyStateName t_State);

	void setFlip(bool t_Flip)			{ m_CurrentFlip = t_Flip; }
	bool getFlip() const				{ return m_CurrentFlip; }

	void setState(EnemiesState * t_NewState);
	RECT getBound() override;

	void Draw(D3DXVECTOR3 t_Pos = D3DXVECTOR3(), RECT t_Rect = RECT(), D3DXVECTOR2 t_Scale = D3DXVECTOR2(),
		D3DXVECTOR2 t_Transform = D3DXVECTOR2(), float t_Angle = 0, D3DXVECTOR2 t_RotationCenter = D3DXVECTOR2(),
		D3DXCOLOR t_TransColor = D3DCOLOR_XRGB(255, 255, 255));

	void Update(float t_GameTime) override;
	void OnCollision(SideCollisions t_Side) override;
};
