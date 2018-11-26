#include "EnemiesBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"


EnemiesBullet::EnemiesBullet()
{
	tag = EnemyBullet;
	pAnim = new Animation(Define::ENEMIES_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	pAnim->setAnimation(0, 1);
	this->setWidth(pAnim->getWidth());
	this->setHeight(pAnim->getHeight());

	bulletY = 25.0f;
	isBurst = false;
	allowDrawSprite = true;
}


EnemiesBullet::~EnemiesBullet()
{
	SAFE_DELETE(pAnim);
}


RECT EnemiesBullet::getBound()
{
	RECT rect;
	rect.left = x - 4;
	rect.top = y - 4;
	rect.right = x + 4;
	rect.bottom = y + 4;

	return rect;
}

void EnemiesBullet::drawSprite(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!allowDrawSprite)
		return;

	pAnim->setPosition(getPosition());
	if (camera)
		pAnim->drawSprite(pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		pAnim->drawSprite(pAnim->getPosition());
}

void EnemiesBullet::update(float dt)
{
	if (!allowDrawSprite)
		return;

	if (!isBurst)
	{
		vy += bulletY;
		if (vy > 300)
			vy = 300;
	}
	else if (pAnim->getPause())// da chay xong animation no
		allowDrawSprite = false;

	pAnim->update(dt);
	Entity::update(dt);
}

void EnemiesBullet::onCollision(SideCollisions side)
{
	isBurst = true;
	vx = 0;
	vy = 0;

	pAnim->setAnimation(1, 3, 0.1, false);
}

void EnemiesBullet::onCollision(Entity* obj)
{
	isBurst = true;
	vx = 0;
	vy = 0;

	pAnim->setAnimation(1, 3, 0.1, false);
}