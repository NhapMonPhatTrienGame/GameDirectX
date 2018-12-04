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
	tag = Tag::RockMan;
	pAnimation = new Animation(Define::ANIMATION_ROCKMAN, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	allowJump = true;
	allowShoot = true;
	allowDash = true;
	isReverse = true;

	isShoot = false;
	alive = false;
	timeShoot = 0.3f;
	timeCurrentShoot = 0.0f;
	timeChangeShoot = 0.0f;
	timeAlive = 0.0f;

	vx = 0;
	vy = 0;
	HP = 20;

	currentState = PlayerState::Fall;
	setState(new AppearState(this));
}

GamePlayer::~GamePlayer()
{
	delete pAnimation;
	delete pState;
	for (auto& bullet : listBullet)
		delete bullet;
	listBullet.clear();
}

void GamePlayer::changeAnimation(PlayerState state)
{
	switch (state)
	{
	case PlayerState::Appear:
		pAnimation->setAnimation(0, 5, 0.15, false);
		break;
	case PlayerState::Stand:
		pAnimation->setAnimation(1, 4, 0.05);
		break;
	case PlayerState::Run:
		pAnimation->setAnimation(3, 10, 0.05);
		break;
	case PlayerState::Jump:
		pAnimation->setAnimation(5, 3, 0.05, false);
		break;
	case PlayerState::Fall:
		pAnimation->setAnimation(7, 3, 0.05, false);
		break;
	case PlayerState::Cling:
		pAnimation->setAnimation(9, 3, 0.05, false);
		break;
	case PlayerState::SlipDown:
		pAnimation->setAnimation(11, 3, 0.05, false);
		break;
	case PlayerState::Dash:
		pAnimation->setAnimation(15, 2, 0.05, false);
		break;
	case PlayerState::Climb:
		break;
	case PlayerState::Bleed:
		pAnimation->setAnimation(17, 9, 0.05);
		break;
	case PlayerState::Die:
		pAnimation->setAnimation(19, 3, 1.0f);
		break;
	case PlayerState::Win: break;
	default: break;
	}

	this->setWidth(pAnimation->getWidth());
	this->setHeight(pAnimation->getHeight());
}

void GamePlayer::setState(GameState* newState)
{
	if (currentState == newState->getState())
		return;

	delete pState;
	pState = newState;
	currentState = newState->getState();
	changeAnimation(newState->getState());
}

Move GamePlayer::getMoveDirection() const
{
	if (vx > 0) return Move::MoveRight;
	if (vx < 0) return Move::MoveRight;
	return Move::None;
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
		case PlayerState::Stand: case PlayerState::Run: case PlayerState::Dash:
		{
			setState(new JumpState(this));
			break;
		}
		case PlayerState::SlipDown:
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
		PlayerShoot(BulletType::Normal);

		allowShoot = false;
		timeCurrentShoot = 0.0f;
		timeChangeShoot = 0;
	}

	if (Key == VK_SLIDE && allowDash)
	{
		allowDash = false;

		switch (currentState)
		{
		case PlayerState::Stand: case PlayerState::Run:
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
		if (currentState == PlayerState::Jump || currentState == PlayerState::Cling)
			vy = 0;
		allowJump = true;
		break;
	}
	case VK_SHOOT:
	{

		if (timeChangeShoot > timeShoot * 3)
		{
			isShoot = true;
			pAnimation->setShoot(isShoot);
			//The second level
			PlayerShoot(BulletType::SecondLevel);
		}
		else
		{
			if (timeChangeShoot > timeShoot * 1.5)
			{
				isShoot = true;
				pAnimation->setShoot(isShoot);
				//The first level
				PlayerShoot(BulletType::FirstLevel);
			}
		}

		allowShoot = true;
		break;
	}
	case VK_SLIDE:
	{
		if (currentState == PlayerState::Dash)
			setState(new StandState(this));
		allowDash = true;
		break;
	}
	default:break;
	}
}

RECT GamePlayer::getBound()
{
	RECT r;
	r.left = x - 13;
	r.right = x + 13;
	r.top = y - 15;
	r.bottom = y + 49 / 2.0f;

	return r;
}

void GamePlayer::update(float dt)
{
	onNoCollisionWithBottom();

	for (auto& bullet : listBullet)
		bullet->update(dt);

	if (isShoot)
	{
		timeCurrentShoot += dt;
		if (timeCurrentShoot > timeShoot)
		{
			isShoot = false;
			pAnimation->setShoot(isShoot);
			timeCurrentShoot = 0.0f;
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
			allowDraw = true;
			timeAlive = 0.0f;
		}
		else
		{
			int TimePause = timeAlive / 0.05f;//0.1 time twinkle
			if (TimePause % 2 == 0)
			{
				allowDraw = true;
			}
			else if (TimePause % 2 == 1)
			{
				allowDraw = false;
			}
		}
	}

	Entity::update(dt);
	pAnimation->update(dt);

	if (pState)
		pState->update(dt);
}

void GamePlayer::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!allowDraw)
		return;

	for (auto& bullet : listBullet)
		bullet->draw(camera);

	pAnimation->setReverse(isReverse);
	pAnimation->setPosition(getPosition());

	if (camera)
		pAnimation->draw(pAnimation->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		pAnimation->draw(pAnimation->getPosition());
}

void GamePlayer::onCollision(SidesCollision side)
{
	if (pState)
		pState->onCollision(side);
}

void GamePlayer::onNoCollisionWithBottom()
{
	if (sideY != SidesCollision::Bottom)
	{
		switch (currentState)
		{
		case PlayerState::Stand:case PlayerState::Run:case PlayerState::Dash:
			setState(new FallState(this));
			break;
		default:break;
		}
	}
}

void GamePlayer::onCollision(Entity* enemies)
{
	if (enemies->getTag() == Tag::Enemy || enemies->getTag() == Tag::EnemyBullet)
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

void GamePlayer::PlayerShoot(::BulletType bulletType)
{
	auto *playerBullet = new PlayerBullet(PlayerBulletState::Fire, bulletType);

	float posX = 0;
	float posY;

	if (bulletType == BulletType::FirstLevel || bulletType == BulletType::SecondLevel)
		posY = this->getBound().top + playerBullet->getHeight() / 4.0f + 15;
	else
		posY = this->getBound().top + playerBullet->getHeight() / 4.0f + 20;

	if (currentState == PlayerState::SlipDown)
	{
		if (!isReverse)
		{
			playerBullet->setReverse(true);
			posX = this->getBound().left + playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(-80);
			playerBullet->setBulletX(-50.f);
		}
		else
		{
			playerBullet->setReverse(false);
			posX = this->getBound().right - playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(80);
			playerBullet->setBulletX(50.f);
		}
	}
	else
	{
		if (!isReverse)
		{
			playerBullet->setReverse(false);
			posX = this->getBound().right - playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(80);
			playerBullet->setBulletX(50.f);
		}
		else
		{
			playerBullet->setReverse(true);
			posX = this->getBound().left + playerBullet->getWidth() / 4.0f;
			playerBullet->setPosition(posX, posY);
			playerBullet->setVx(-80);
			playerBullet->setBulletX(-50.f);
		}
	}

	listBullet.push_back(playerBullet);
}