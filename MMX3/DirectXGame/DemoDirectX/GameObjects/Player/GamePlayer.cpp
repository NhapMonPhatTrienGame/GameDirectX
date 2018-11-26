#include "GamePlayer.h"
#include "GameState/FallState/FallState.h"
#include "GameState/JumpState/JumpState.h"
#include "GameState/JumpState/ClingState.h"
#include "../../GameComponents/GameGlobal.h"
#include "GameState/AppearState/AppearState.h"
#include <iostream>
#include "GameState/DashState/DashState.h"
#include "GameState/DieState/DieState.h"
#include "GameState/StandState/StandState.h"
#include "GameState/BleedState/BleedState.hpp"
#include "../../GameDefines/GameDefine.h"


GamePlayer::GamePlayer()
{
	tag = RockMan;
	pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	allowJump = true;
	allowShoot = true;
	allowDash = true;

	isShoot = false;
	alive = false;
	timeShoot = 0.5f;
	timeCurrentShoot = 0.0f;
	timeChangeShoot = 0.0f;
	timeAlive = 0.0f;

	vx = 0;
	vy = 0;
	HP = 20;

	currentState = Fall;
	setState(new AppearState(this));
}

GamePlayer::~GamePlayer()
{
	SAFE_DELETE(pState);
	SAFE_DELETE(pAnimation);
	for (auto& bullet : listPlayerBullet)
		delete bullet;
}

void GamePlayer::changeAnimation(StateName state)
{
	switch (state)
	{
	case Appear:
		pAnimation->setAnimation(0, 5, 0.15, false);
		break;
	case Stand:
		pAnimation->setAnimation(1, 4, 0.05);
		break;
	case Run:
		pAnimation->setAnimation(3, 10, 0.05);
		break;
	case Jump:
		pAnimation->setAnimation(5, 3, 0.05, false);
		break;
	case Fall:
		pAnimation->setAnimation(7, 3, 0.05, false);
		break;
	case Cling:
		pAnimation->setAnimation(9, 3, 0.05, false);
		break;
	case SlipDown:
		pAnimation->setAnimation(11, 3, 0.05, false);
		break;
	case Dash:
		pAnimation->setAnimation(15, 2, 0.05, false);
		break;
	case Climb:
		break;
	case Bleed:
		pAnimation->setAnimation(17, 9, 0.05);
		break;
	case Die:
		pAnimation->setAnimation(19, 3, 1.0f);
		break;
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

GamePlayer::MoveDirection GamePlayer::getMoveDirection() const
{
	if (vx > 0) return MoveToRight;
	if (vx < 0) return MoveToLeft;
	return None;
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
		case Stand: case Run: case Dash:
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
			PlayerShoot(PlayerBullet::Normal);
		}

		allowShoot = false;
		timeCurrentShoot = 0.0f;
		timeChangeShoot = 0.0f;
	}

	if (Key == VK_SLIDE && allowDash)
	{
		allowDash = false;

		switch (currentState)
		{
		case Stand: case Run:
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
			if (currentState == Jump || currentState == Cling)
				vy = 0;
			allowJump = true;
			break;
		}
	case VK_SHOOT:
		{
			if (timeChangeShoot > timeShoot * 2)
			{
				isShoot = true;
				pAnimation->setShoot(isShoot);
				//The second level
				PlayerShoot(PlayerBullet::SecondLevel);
			}
			else
			{
				if (timeChangeShoot > timeShoot)
				{
					isShoot = true;
					pAnimation->setShoot(isShoot);
					//The first level
					PlayerShoot(PlayerBullet::FirstLevel);
				}
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
	default:break;
	}
}

RECT GamePlayer::getBound()
{
	RECT rect;
	rect.left = x - 13;
	rect.right = x + 13;
	rect.top = y - 15;
	rect.bottom = y + 49 / 2.0f;

	return rect;
}

void GamePlayer::update(float dt)
{
	onNoCollisionWithBottom();

	for (auto& bullet : listPlayerBullet)
		bullet->update(dt);
	
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
		timeChangeShoot += dt;

	//thời gian bất tử
	if (alive)
	{
		timeAlive += dt;
		if (timeAlive > 1.5f)
		{
			alive = false;
			allowDrawSprite = true;
			timeAlive = 0.0f;
		}
		else
		{
			int TimePause = timeAlive / 0.1f;//0.1 time twinkle
			if (TimePause % 2 == 0)
			{
				allowDrawSprite = true;
			}
			else if (TimePause % 2 == 1)
			{
				allowDrawSprite = false;
			}
		}
	}

	Entity::update(dt);
	pAnimation->update(dt);

	if (pState)
		pState->update(dt);
}

void GamePlayer::drawSprite(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	for (auto& bullet : listPlayerBullet)
		bullet->drawSprite(camera);

	if (!allowDrawSprite)
		return;

	pAnimation->setFlip(currentReverse);
	pAnimation->setPosition(getPosition());
	if (camera)
		pAnimation->drawSprite(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		pAnimation->drawSprite(pAnimation->getPosition());
}

void GamePlayer::onCollision(SideCollisions side)
{
	if (pState)
		pState->onCollision(side);
}

void GamePlayer::onNoCollisionWithBottom()
{
	if (sideY != Bottom)
	{
		switch (currentState)
		{
		case Stand:case Run:case Dash:
			setState(new FallState(this));
			break;
		default:break;
		}
	}
}

void GamePlayer::onCollision(Entity* enemies)
{
	if (enemies->getTag() == Enemy || enemies->getTag() == EnemyBullet)
	{
		if (alive)
			return;

		HP -= 1.0f;
		alive = true;
		if (HP <= 0)
		{
			setState(new DieState(this));
			alive = false;
			return;
		}

		if (enemies->getVx() > 0 || x < enemies->getPosition().x)
			setState(new BleedState(this, 1));
		else
		{
			if (enemies->getVx() < 0 || x >= enemies->getPosition().x)
				setState(new BleedState(this, -1));
		}
	}
}

void GamePlayer::PlayerShoot(PlayerBullet::BulletType bulletType)
{
	auto *playerBullet = new PlayerBullet(PlayerBullet::Fire, bulletType);

	float posX = 0;
	float posY = this->getBound().top + playerBullet->getHeight() / 4.0f + 15;

	if (currentState == SlipDown)
	{
		if (!currentReverse)
		{
			playerBullet->setCurrentFlip(true);
			posX = this->getBound().left + playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(-80);
			playerBullet->setBulletX(-50.f);
		}
		else
		{
			playerBullet->setCurrentFlip(false);
			posX = this->getBound().right - playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(80);
			playerBullet->setBulletX(50.f);
		}
	}
	else
	{
		if (!currentReverse)
		{
			playerBullet->setCurrentFlip(false);
			posX = this->getBound().right - playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(80);
			playerBullet->setBulletX(50.f);
		}
		else
		{
			playerBullet->setCurrentFlip(true);
			posX = this->getBound().left + playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(-80);
			playerBullet->setBulletX(-50.f);
		}
	}

	listPlayerBullet.push_back(playerBullet);
}