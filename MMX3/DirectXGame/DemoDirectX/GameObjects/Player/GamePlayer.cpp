#include "GamePlayer.h"
#include "GameState/StandState/StandState.h"
#include "GameState/FallState/FallState.h"
#include "GameState/JumpState/JumpState.h"
#include "GameState/JumpState/ClingState.h"
#include "../../GameComponents/GameGlobal.h"
#include "GameState/AppearState/AppearState.h"
#include <iostream>
#include "GameState/DashState/DashState.h"


GamePlayer::GamePlayer()
{
	Tag = RockMan;
	pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	allowJump = true;
	allowShoot = true;
	allowDash = true;

	isShoot = false;
	timeShoot = 0.3f;
	timeCurrentShoot = 0.0f;
	timeChargedShoot = 0.0f;

	vx = 0;
	vy = 0;
	HP = 20;

	currentState = Falling;
	setState(new AppearState(this));
}

GamePlayer::~GamePlayer()
{
	SAFE_DELETE(pState);
	SAFE_DELETE(pAnimation);
}

void GamePlayer::changeAnimation(StateName state)
{
	switch (state)
	{
	case Appear:
		pAnimation->setAnimation(0, 5, 0.1, false);
		break;
	case Standing:
		pAnimation->setAnimation(1, 4, 0.5);
		break;
	case Running:
		pAnimation->setAnimation(3, 10, 0.05);
		break;
	case Jumping:
		pAnimation->setAnimation(5, 3, 0.05, false);
		break;
	case Falling:
		pAnimation->setAnimation(7, 3, 0.05, false);
		break;
	case Cling:
		pAnimation->setAnimation(9, 4, 0.05, false);
		break;
	case SlipDown:
		pAnimation->setAnimation(11, 3, 0.05, false);
		break;
	case Dash:
		pAnimation->setAnimation(16, 2, 0.05, false);
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
	if (currentState == newState->getState())
		return;
	SAFE_DELETE(pState);
	pState = newState;
	changeAnimation(newState->getState());
	currentState = newState->getState();
}

void GamePlayer::handlerKeyBoard(const std::map<int, bool>& keys, float dt) const
{
	if (pState)
		pState->handlerKeyBoard(keys, dt);
}

void GamePlayer::onKeyDown(std::map<int, bool> keys, int Key)
{

	if (Key == VK_JUMP && allowJump)
	{
		allowJump = false;
		switch (currentState)
		{
		case Standing: case Running: case Dash:
		{
			setState(new JumpState(this));
			break;
		}
		case SlipDown:
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

	if (Key == VK_SHOOT && allowShoot)
	{
		if (!isShoot)
		{
			isShoot = true;
			pAnimation->setShoot(isShoot);
		}
		//Add Buster shot

		allowShoot = false;
		timeCurrentShoot = 0.0f;
		timeChargedShoot = 0.0f;
	}

	if (Key == VK_SLIDE && allowDash)
	{
		allowDash = false;

		switch (currentState)
		{
		case Standing: case Running:
			setState(new DashState(this));
			break;
		default: break;
		}
	}
}

void GamePlayer::onKeyUp(int Key)
{
	switch (Key)
	{
	case VK_JUMP:
	{
		//if gameplayer Jumping or cling, it will fall
		if (currentState == Jumping || currentState == Cling)
			vy = 0;

		allowJump = true;
		break;
	}

	case VK_SHOOT:
	{
		if (timeChargedShoot > timeShoot * 3)
		{
			isShoot = true;
			pAnimation->setShoot(isShoot);
			//Add lv2 charged shot

		}
		else
			if (timeChargedShoot > timeShoot * 2)
			{
				isShoot = true;
				pAnimation->setShoot(isShoot);
				//Add lv1 charged shot

			}

		allowShoot = true;
		break;
	}

	case VK_SLIDE:
	{
		if (currentState == Dash)
			setState(new StandState(this));

		allowDash = true;
		break;
	}
	default:
		break;
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

void GamePlayer::update(float dt)
{
	onNoCollisionWithBottom();

	if (isShoot)
	{
		timeCurrentShoot += dt;
		if (timeCurrentShoot > timeShoot)
		{
			isShoot = false;
			pAnimation->setShoot(isShoot);
			timeCurrentShoot = 0;
		}
	}

	if (!allowShoot)
	{
		timeChargedShoot += dt;
	}

	Entity::update(dt);

	pAnimation->update(dt);
	if (pState)
		pState->update(dt);


}

void GamePlayer::drawSprite(Camera*	pCamera, D3DXVECTOR3 Position, RECT SourceRect, D3DXVECTOR2 Scale, D3DXVECTOR2 Translate,
                      float Angle, D3DXVECTOR2 RotationCenter, D3DXCOLOR TransColor)
{
	pAnimation->setFlip(currentReverse);
	pAnimation->setPosition(getPosition());

	if (pCamera)
	{
		pAnimation->drawSprite(D3DXVECTOR3(x, y, 0), SourceRect, Scale, pCamera->getTrans(), Angle, RotationCenter, TransColor);
	}
	else
		pAnimation->drawSprite(D3DXVECTOR3(x, y, 0));
}

void GamePlayer::onCollision(SideCollisions side)
{
	pState->onCollision(side);
}

void GamePlayer::onCollision(Entity *enemy)
{
	switch (enemy->Tag)
	{
	case Entity::Brick:
		break;
	case Entity::Enemy:
	{
		//HP -= enemy->getDame();
		if (HP <= 0)
		{
			//setState(new DieState(this));
			return;
		}
			
		//setState(new BleedState(this));
	}
		break;
	case Entity::Mario:
		break;
	case Entity::Static:
		break;
	case Entity::BrickGoldNormal:
		break;
	case Entity::BrickGoldBeEaten:
		break;
	case Entity::Unknown:
		break;
	default:
		break;
	}
}

void GamePlayer::onNoCollisionWithBottom()
{
	if (sideY != Bottom)
	{
		switch (currentState)
		{
		case MegaManState::Standing: case MegaManState::Running: case MegaManState::Dash:
			setState(new FallState(this));
			break;

		default:
			break;
		}
	}
}
