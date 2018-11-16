#include "Enemies.h"
#include "EnemiesStandState.h"


Enemies::Enemies()
{
	Tag = Enemy;
	m_Animation[0] = new Animation(Define::ENEMIES_STAND, 1, 2, 48, 48, 0.15);
	m_Animation[1] = new Animation(Define::ENEMIES_JUMP, 1, 2, 48, 48, 0.15);
	m_Animation[2] = new Animation(Define::ENEMIES_GUN, 1, 4, 48, 48, 0.15);

	m_CurrentAnimation = m_Animation[0];
}

Enemies::~Enemies()
{
	SAFE_DELETE(m_State);
	SAFE_DELETE(m_CurrentAnimation);
}

void Enemies::ChangeAnimation(EnemyState::EnemyStateName t_State)
{
	switch (t_State)
	{
	case EnemyState::Stand:
		m_CurrentAnimation = m_Animation[0];
		break;
	case EnemyState::Jump:
		m_CurrentAnimation = m_Animation[1];
		break;
	case EnemyState::Attack:
		m_CurrentAnimation = m_Animation[2];
		break;
	case EnemyState::Die: break;
	default: break;
	}

	this->setWidth(m_CurrentAnimation->getWidth());
	this->setHeight(m_CurrentAnimation->getHeight());
}


void Enemies::setState(EnemiesState* t_NewState)
{
	if (m_CurrentState == t_NewState->getState())
		return;
	SAFE_DELETE(m_State);
	m_State = t_NewState;
	ChangeAnimation(t_NewState->getState());
	m_CurrentState = t_NewState->getState();
}

RECT Enemies::getBound()
{
	RECT rect;
	rect.left = x - getWidth() / 2.0f;
	rect.right = rect.left + getWidth();
	rect.top = y - getHeight() / 2.0f;
	rect.bottom = rect.top + getHeight();
	return rect;
}

void Enemies::Draw(D3DXVECTOR3 t_Pos, RECT t_Rect, D3DXVECTOR2 t_Scale, D3DXVECTOR2 t_Transform, float t_Angle,
	D3DXVECTOR2 t_RotationCenter, D3DXCOLOR t_TransColor)
{
	m_CurrentAnimation->setFlip(m_CurrentFlip);
	m_CurrentAnimation->setPosition(getPosition());

	m_CurrentAnimation->Draw(D3DXVECTOR3(x, y, 0), t_Rect, t_Scale, t_Transform, t_Angle, t_RotationCenter, t_TransColor);
}

void Enemies::Update(float t_GameTime)
{
	m_CurrentAnimation->Update(t_GameTime);
	if (m_State)
		m_State->Update(t_GameTime);
	Entity::Update(t_GameTime);
}

void Enemies::OnCollision(SideCollisions t_Side)
{
	if (m_State)
		m_State->OnCollision(t_Side);
}
