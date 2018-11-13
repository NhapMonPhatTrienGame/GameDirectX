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

	allowJump = true;
	allowShoot = true;
	allowSlide = true;

	mShoot = false;
	mTimeShoot = 0.5f;
	mTimeCurrentShoot = 0.0f;

	vx = 0;
	vy = 0;
	HP = 20;
	currentState = Falling;
	setState(new AppearState(this));
}

void GamePlayer::ChangeAnimation(StateName state)
{
	switch (state)
	{
		case Appear:
			pAnimation->SetAnimation(0, 5, 0.15, false);
			break;
		case Standing:
			pAnimation->SetAnimation(1, 4, 0.1);
			break;
		case Running:
			pAnimation->SetAnimation(3, 10, 0.1);
			break;
		case Jumping:
			pAnimation->SetAnimation(5, 3, 0.1, false);
			break;
		case Falling:
			pAnimation->SetAnimation(7, 3, 0.1, false);
			break;
		case Cling:
			pAnimation->SetAnimation(9, 3, 0.1, false);
			break;
		case SlideVertical:
			pAnimation->SetAnimation(11, 3, 0.1, false);
			break;
		case SlideHorizontal:
			pAnimation->SetAnimation(15, 2, 0.1, false);
			break;
		case Climb:
		case Bleed:
		case Die:
		case Win:break;

		default: break;
	}

	this->width = pAnimation->GetWidth();
	this->height = pAnimation->GetHeight();
}

void GamePlayer::setState(GameState* newState)
{
	if (currentState == newState->getState())
		return;
	SAFE_DELETE(pState);
	pState = newState;
	ChangeAnimation(newState->getState());
	currentState = newState->getState();
}
StateName GamePlayer::getState() const
{
	return currentState;
}
Animation* GamePlayer::GetAnimation() const
{
	return pAnimation;
}

void GamePlayer::SetCamera(Camera* camera)
{
	pCamera = camera;
}

float GamePlayer::getHP() const
{
	return HP;
}
void GamePlayer::setHP(float hp)
{
	HP = hp;
}
void GamePlayer::addHP(float hp)
{
	HP += hp;
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
	if (Key == VK_JUMP && allowJump)
	{
		allowJump = false;
		switch (currentState)
		{
			case Standing:case Running:case SlideHorizontal:
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
	
	if (Key == VK_SHOOT && allowShoot && !mShoot)
	{
		mShoot = true;
		pAnimation->SetShoot(mShoot);
		allowShoot = false;
	}
	
	if(Key == VK_SLIDE && allowSlide)
	{
		allowSlide = false;

		switch(currentState)
		{
			case Standing:case Running:
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
		allowJump = true;
	}
	else if (Key == VK_SHOOT)
	{
		allowShoot = true;
	}
	else if(Key == VK_SLIDE)
	{
		allowSlide = true;
	}
}

void GamePlayer::SetReverse(bool flag)
{
	isCurrentReverse = flag;
}

bool GamePlayer::getReverse() const
{
	return isCurrentReverse;
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
	if(mShoot)
	{
		mTimeCurrentShoot += dt;
		if(mTimeCurrentShoot > mTimeShoot)
		{
			mShoot = false;
			pAnimation->SetShoot(mShoot);
			mTimeCurrentShoot = 0;
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
	pAnimation->SetFlip(isCurrentReverse);
	pAnimation->SetPosition(getPosition());

	if (pCamera)
	{
		const auto trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2.0f - pCamera->GetPosition().x,
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
	if (currentState == Appear || currentState == Falling || currentState == Jumping || currentState == SlideVertical || currentState == Cling)
		return;

	setState(new FallState(this));
}