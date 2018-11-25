#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"


PlayerBullet::PlayerBullet(BulletState state, BulletType type)
{
	tag = RockManBullet;
	pAnims = new Animation(Define::PLAYER_BULLET, 6, 7, 46, 32, D3DCOLOR_XRGB(100, 100, 100));

	bulletX = 25.0f;
	isBurst = false;
	currentFlip = false;

	bulletState = state;
	bulletType = type;
	changeBullet(state, type);
}

PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(pAnims);
}

void PlayerBullet::changeBullet(BulletState state, BulletType type)
{
	switch (state)
	{
	case Fire:
		{
			switch (type)
			{
			case Normal:
				pAnims->setAnimation(0, 1);
				break;
			case FirstLevel:
				pAnims->setAnimation(2, 6, 0.15, false);
				break;
			case SecondLevel:
				pAnims->setAnimation(3, 3, 0.15, false);
				break;
			default: break;
			}
		}
	case Burst:
		{
			switch (type)
			{
			case BurstNormal:
				pAnims->setAnimation(1, 3, 0.15, false);
				break;
			case BurstFirstLevel:
				pAnims->setAnimation(4, 7, 0.15, false);
				break;
			case BurstSecondLevel:
				pAnims->setAnimation(5, 7, 0.15, false);
				break;
			default: break;
			}
		}
	default: break;
	}

	this->setWidth(pAnims->getWidth());
	this->setHeight(pAnims->getHeight());

}

RECT PlayerBullet::getBound()
{
	RECT rect;
	rect.left = x + getWidth() / 4.0f;
	rect.right = rect.left - getWidth() / 2.0f;
	rect.top = y + getHeight() / 4.0f;
	rect.bottom = rect.top - getHeight() / 2.0f;
	return rect;
}

void PlayerBullet::drawSprite(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!allowDrawSprite)
		return;

	pAnims->setPosition(this->getPosition());
	pAnims->setFlip(currentFlip);
	if (camera)
		pAnims->drawSprite(pAnims->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		pAnims->drawSprite(pAnims->getPosition());
}

void PlayerBullet::update(float dt)
{
	if (!allowDrawSprite)
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
		allowDrawSprite = false;

	pAnims->update(dt);
	Entity::update(dt);
}

void PlayerBullet::onCollision(SideCollisions side)
{
	isBurst = true;
	vx = vy = 0;
	bulletState = Burst;

	switch(bulletType)
	{
	case Normal:
		bulletType = BurstNormal;
		break;
	case FirstLevel:
		bulletType = BurstFirstLevel;
		break;
	case SecondLevel:
		bulletType = BurstSecondLevel;
		break;
	default: break;
	}

	changeBullet(bulletState, bulletType);
}

void PlayerBullet::onCollision(Entity* obj)
{
	isBurst = true;
	vx = vy = 0;
	bulletState = Burst;

	switch (bulletType)
	{
	case Normal:
		bulletType = BurstNormal;
		break;
	case FirstLevel:
		bulletType = BurstFirstLevel;
		break;
	case SecondLevel:
		bulletType = BurstSecondLevel;
		break;
	default: break;
	}

	changeBullet(bulletState, bulletType);
}