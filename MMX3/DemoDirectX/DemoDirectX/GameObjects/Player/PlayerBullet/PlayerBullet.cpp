#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet(PlayerBulletState state, BulletType type)
{
	tag = Tag::RockManBullet;
	pAnims = new Animation(Define::PLAYER_BULLET, 6, 7, 46, 31, D3DCOLOR_XRGB(100, 100, 100));

	bulletX = 25.0f;
	isBurst = false;
	isReverse = false;

	bulletState = state;
	bulletType = type;
	changeBullet(state, type);
	allowDraw = true;
}

PlayerBullet::~PlayerBullet()
{
	delete pAnims;
}

void PlayerBullet::changeBullet(PlayerBulletState state, BulletType type)
{
	switch (state)
	{
	case PlayerBulletState::Fire:
	{
		switch (type)
		{
		case BulletType::Normal:
			pAnims->setAnimation(0, 1);
			this->setWidth(8);
			this->setHeight(6);
			break;
		case BulletType::FirstLevel:
			pAnims->setAnimation(2, 6, 0.1);
			this->setWidth(30);
			this->setHeight(20);
			break;
		case BulletType::SecondLevel:
			pAnims->setAnimation(3, 3, 0.1);
			this->setWidth(40);
			this->setHeight(28);
			break;
		default: break;
		}
	}
	case PlayerBulletState::Burst:
	{
		switch (type)
		{
		case BulletType::BurstNormal:
			pAnims->setAnimation(1, 3, 0.05, false);
			break;
		case BulletType::BurstFirstLevel:
			pAnims->setAnimation(4, 7, 0.05, false);
			break;
		case BulletType::BurstSecondLevel:
			pAnims->setAnimation(5, 7, 0.05, false);
			break;
		default: break;
		}
	}
	default: break;
	}
}

RECT PlayerBullet::getBound()
{
	RECT rect;

	rect.left = x - getWidth() / 2.0f;
	rect.top = y - getHeight() / 2.0f;
	rect.right = rect.left + getWidth();
	rect.bottom = rect.top + getHeight();
	return rect;
}

void PlayerBullet::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!GameCollision::isCollision(getBound(), camera->getBound()))
	{
		allowDraw = false;
		isBurst = true;
	}

	if (!allowDraw)
		return;

	pAnims->setPosition(this->getPosition());
	pAnims->setReverse(isReverse);
	if (camera)
		pAnims->draw(pAnims->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		pAnims->draw(pAnims->getPosition());
}

void PlayerBullet::update(float dt)
{
	if (!allowDraw)
		return;

	if (!isBurst)
	{
		vx += bulletX;
		if (vx > 300)
			vx = 300;
		else if (vx < -300)
			vx = -300;
	}
	else if (pAnims->getPause())
		allowDraw = false;

	Entity::update(dt);
	pAnims->update(dt);
}

void PlayerBullet::onCollision(SidesCollision side)
{
	isBurst = true;
	vx = vy = 0;
	bulletState = PlayerBulletState::Burst;

	switch (bulletType)
	{
	case BulletType::Normal:
		bulletType = BulletType::BurstNormal;
		break;
	case BulletType::FirstLevel:
		bulletType = BulletType::BurstFirstLevel;
		break;
	case BulletType::SecondLevel:
		bulletType = BulletType::BurstSecondLevel;
		break;
	default: break;
	}

	changeBullet(bulletState, bulletType);
}

void PlayerBullet::onCollision(Entity* obj)
{
	isBurst = true;
	vx = vy = 0;
	bulletState = PlayerBulletState::Burst;

	switch (bulletType)
	{
	case BulletType::Normal:
		bulletType = BulletType::BurstNormal;
		break;
	case BulletType::FirstLevel:
		bulletType = BulletType::BurstFirstLevel;
		break;
	case BulletType::SecondLevel:
		bulletType = BulletType::BurstSecondLevel;
		break;
	default: break;
	}

	changeBullet(bulletState, bulletType);
}