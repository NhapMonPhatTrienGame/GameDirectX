#include "GamePlayer.h"
#include "GameState/FallState/FallState.h"
#include "GameState/JumpState/JumpState.h"
#include "../../GameComponents/GameGlobal.h"
#include "GameState/SlideState/SlideHorizontalState/SlideHorizontalState.h"
#include "GameState/AppearState/AppearState.h"
#include <iostream>

GamePlayer::GamePlayer()
{
	pAnimation = new Animation("Resources/mario/Rockman_49x49_backfround(100,100,100).png", 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	allowJump = true;
	allowShoot = true;
	allowSlide = true;

	mShoot = false;
	mTimeShoot = 0.5f;
	mTimeCurrentShoot = 0.0f;

	vx = 0;
	vy = 0;
	setState(new AppearState(this));
}

GamePlayer::~GamePlayer() {}

void GamePlayer::ChangeAnimation(StateName state)
{
	switch (state)
	{
		case Appear:
			pAnimation->setAnimation(0, 5, 0.5);
			break;
		case Standing:
			pAnimation->setAnimation(1, 4, 0.15);
			break;
		case Running:
			pAnimation->setAnimation(3, 10, 0.1);
			break;
		case Jumping:
			pAnimation->setAnimation(5, 3, 0.5, 1);
			break;
		case Falling:
			pAnimation->setAnimation(7, 3, 0.5, 1);
			break;
		case SlideHorizontal:
			pAnimation->setAnimation(15, 2, 0.15);
			break;
		case SlideVertical:
			pAnimation->setAnimation(11, 2, 0.15, 1);
			break;
		default: break;
	}

	this->width = pAnimation->GetWidth();
	this->height = pAnimation->GetHeight();
}

void GamePlayer::setState(GameState* newState)
{
	SAFE_DELETE(pState);
	pState = newState;
	ChangeAnimation(newState->getState());
	currentState = newState->getState();
}
StateName GamePlayer::getState() const
{
	return currentState;
}

void GamePlayer::SetCamera(Camera* camera)
{
	pCamera = camera;
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

void GamePlayer::OnKeyDown(int Key)
{
	if (Key == VK_JUMP && allowJump)
	{
		allowJump = false;

		switch (currentState)
		{
			case Standing: case Running: case SlideHorizontal:
				setState(new JumpState(this));
				break;
			default: break;
		}
	}
	else if (Key == VK_SHOOT && allowShoot)
	{
		allowShoot = false;

		switch (currentState)
		{
			case Standing:
				pAnimation->setAnimation(2, 2, 0.5);
				break;
			case Running:
				pAnimation->setAnimation(4, 10, 0.1);
				break;
			case Jumping:
				pAnimation->setAnimation(6, 3, 0.5, 1);
				break;
			case Falling:
				pAnimation->setAnimation(8, 3, 0.5, 1);
				break;
			case SlideHorizontal:
				pAnimation->setAnimation(16, 2, 0.15);
				break;
			default: break;
		}
	}
	else if(Key == VK_SLIDE && allowSlide)
	{
		allowSlide = false;

		switch(currentState)
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
		allowJump = true;

	else if (Key == VK_SHOOT)
	{
		allowShoot = true;

		switch(currentState)
		{
			case Standing:
				pAnimation->setAnimation(1, 4, 0.1);
				break;
			case Running:
				pAnimation->setAnimation(3, 10, 0.1);
				break;
			case Jumping:
				pAnimation->setAnimation(5, 3, 0.5, 1);
				break;
			case Falling:
				pAnimation->setAnimation(7, 3, 0.5, 1);
				break;
			case SlideHorizontal:
				pAnimation->setAnimation(15, 2, 0.15);
				break;
			default: break;
		}
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
	rect.left = x - pAnimation->GetWidth() / 2.0f;
	rect.right = rect.left + pAnimation->GetWidth();
	rect.top = y - pAnimation->GetHeight() / 2.0f;
	rect.bottom = rect.top + pAnimation->GetHeight();

	return rect;
}

void GamePlayer::Update(float dt)
{
	/*if(mShoot)
	{
		mTimeCurrentShoot += dt;
		if(mTimeCurrentShoot > mTimeShoot)
		{
			mShoot = false;
			pAnimation->SetShoot(mShoot);
			mTimeCurrentShoot = 0;
		}
	}*/

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

void GamePlayer::OnCollision(CollisionReturn data, SideCollisions side)
{
	pState->OnCollision(data, side);
}

void GamePlayer::OnNoCollisionWithBottom()
{
	if (currentState == Appear)
		return;
	if (currentState != Jumping && currentState != Falling)
		setState(new FallState(this));
}