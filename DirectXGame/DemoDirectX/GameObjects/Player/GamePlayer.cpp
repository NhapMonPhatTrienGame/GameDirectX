#include "GamePlayer.h"
#include "GameState/FallState/FallState.h"
#include "GameState/JumpState/JumpState.h"
#include "GameState/JumpState/ClingState.h"
#include "../../GameComponents/GameGlobal.h"
#include "GameState/SlideState/SlideHorizontalState/SlideHorizontalState.h"
#include "GameState/AppearState/AppearState.h"
#include <iostream>


GamePlayer::GamePlayer()
{
	Tag = Rockman;
	pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	m_AllowJump = true;
	m_AllowShoot = true;
	m_AllowSlide = true;

	m_Shoot = false;
	m_TimeShoot = 0.5f;
	m_TimeCurrentShoot = 0.0f;

	vx = 0;
	vy = 0;
	m_HP = 20;
	m_CurrentState = Falling;
	setState(new AppearState(this));
}

GamePlayer::~GamePlayer()
{
	SafeDelete(pState);
	SafeDelete(pAnimation);
}

void GamePlayer::ChangeAnimation(StateName state)
{
	switch (state)
	{
	case Appear:
		pAnimation->setAnimation(0, 5, 0.15, false);
		break;
	case Standing:
		pAnimation->setAnimation(1, 4, 0.1);
		break;
	case Running:
		pAnimation->setAnimation(3, 10, 0.1);
		break;
	case Jumping:
		pAnimation->setAnimation(5, 3, 0.1, false);
		break;
	case Falling:
		pAnimation->setAnimation(7, 3, 0.1, false);
		break;
	case Cling:
		pAnimation->setAnimation(9, 3, 0.1, false);
		break;
	case SlideVertical:
		pAnimation->setAnimation(11, 3, 0.1, false);
		break;
	case SlideHorizontal:
		pAnimation->setAnimation(15, 2, 0.1, false);
		break;
	case Climb:
	case Bleed:
	case Die:
	case Win: break;

	default: break;
	}

	this->setWidth(pAnimation->getWidth());
	this->setHeight(pAnimation->getHeight());
}

void GamePlayer::setState(GameState* newState)
{
	if (m_CurrentState == newState->getState())
		return;
	SAFE_DELETE(pState);
	pState = newState;
	ChangeAnimation(newState->getState());
	m_CurrentState = newState->getState();
}

GamePlayer::MoveDirection GamePlayer::getMoveDirection() const
{
	if (vx > 0) return MoveToRight;
	if (vx < 0) return MoveToLeft;
	return None;
}

void GamePlayer::HandleKeyboard(const std::map<int, bool>& keys, float dt) const
{
	if (pState)
		pState->HandleKeyboard(keys, dt);
}

void GamePlayer::OnKeyDown(std::map<int, bool> keys, int Key)
{
	if (Key == VK_JUMP && m_AllowJump)
	{
		m_AllowJump = false;
		switch (m_CurrentState)
		{
		case Standing: case Running: case SlideHorizontal:
		{
			setState(new JumpState(this));
			break;
		}
		case SlideVertical:
		{
			if (keys[VK_SLIDE])
				setState(new ClingState(this, true));
			else
				setState(new ClingState(this));
			break;
		}
		default: break;
		}
	}

	if (Key == VK_SHOOT && m_AllowShoot && !m_Shoot)
	{
		m_Shoot = true;
		pAnimation->setShoot(m_Shoot);
		m_AllowShoot = false;
	}

	if (Key == VK_SLIDE && m_AllowSlide)
	{
		m_AllowSlide = false;

		switch (m_CurrentState)
		{
		case Standing: case Running:
			setState(new SlideHorizontalState(this));
			break;
		default: break;
		}
	}
}

void GamePlayer::OnKeyUp(int Key)
{
	if (Key == VK_JUMP)
	{
		vy = 0;
		m_AllowJump = true;
	}
	else if (Key == VK_SHOOT)
	{
		m_AllowShoot = true;
	}
	else if (Key == VK_SLIDE)
	{
		m_AllowSlide = true;
	}
}

RECT GamePlayer::getBound()
{
	RECT rect;
	rect.left = x - 15;
	rect.right = x + 15;
	rect.top = y - 17;
	rect.bottom = y + 49 / 2.0f;

	return rect;
}

void GamePlayer::Update(float dt)
{
	if (m_Shoot)
	{
		m_TimeCurrentShoot += dt;
		if (m_TimeCurrentShoot > m_TimeShoot)
		{
			m_Shoot = false;
			pAnimation->setShoot(m_Shoot);
			m_TimeCurrentShoot = 0;
		}
	}

	pAnimation->Update(dt);

	if (pState)
		pState->Update(dt);

	Entity::Update(dt);
}

void GamePlayer::Draw(D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate,
                      float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR TransColor)
{
	pAnimation->setFlip(m_CurrentReverse);
	pAnimation->setPosition(getPosition());

	if (pCamera)
	{
		D3DXVECTOR2 trans(GameGlobal::GetWidth() / 2.0f - pCamera->GetPosition().x, 
			GameGlobal::GetHeight() / 2.0f - pCamera->GetPosition().y);
		pAnimation->Draw(D3DXVECTOR3(x, y, 0), SourceRect, Scale, trans, Angle, RotationCenter, TransColor);
	}
	else
		pAnimation->Draw(D3DXVECTOR3(x, y, 0));
}

void GamePlayer::OnCollision(SideCollisions side)
{
	pState->OnCollision(side);
}

void GamePlayer::OnNoCollisionWithBottom()
{
	if (m_CurrentState == Appear || m_CurrentState == Falling || m_CurrentState == Jumping || m_CurrentState == SlideVertical ||
		m_CurrentState == Cling)
		return;

	setState(new FallState(this));
}
