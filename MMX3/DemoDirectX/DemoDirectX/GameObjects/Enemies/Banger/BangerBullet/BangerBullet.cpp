#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	tag = Tag::EnemyBullet;
	anim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	animBurst = new Animation(Define::BURST, 1, 10, 50, 46, 0.1);
	BangerBullet::changeState(BulletState::Fire);

	bulletY = 25.0f;
	isBurst = false;
	allowDraw = true;
}


BangerBullet::~BangerBullet()
{
	delete anim;
	delete animBurst;
}

RECT BangerBullet::getBound()
{
	RECT r = RECT();

	switch (bulletState)
	{
	case BulletState::Fire:
		r.left = x - 4;
		r.top = y - 4;
		r.right = x + 4;
		r.bottom = y + 4;
		break;
	case BulletState::Burst:
	{
		r.left = x - 39 / 2.0f;
		r.right = r.left + 39;
		r.top = y - 41 / 2.0f;
		r.bottom = r.top + 41;
		break;
	}
	default:break;
	}

	return r;
}

void BangerBullet::newBullet(float bx, float by, bool direction)
{
	x = bx;
	y = by;
	//vy = -450;
	vy = -500;
	if (direction)
		//vx = 70;
		vx = 300;
	else
		//vx = -70;
		vx = -300;

	changeState(BulletState::Fire);
	isBurst = false;
	allowDraw = true;
}

void BangerBullet::update(float dt)
{
	if (!allowDraw)
		return;

	if (!isBurst)
	{
		vy += bulletY;
		if (vy > 300)
			vy = 300;
	}
	else if (anim->getPause() || animBurst->getPause())// da chay xong animation no
		allowDraw = false;

	if (bulletState == BulletState::Burst)
		animBurst->update(dt);
	else
		anim->update(dt);

	Entity::update(dt);
}

void BangerBullet::onCollision(SidesCollision side)
{
	vx = 0;
	vy = 0;
	isBurst = true;
	changeState(BulletState::Burst);
}

void BangerBullet::onCollision(Entity* obj)
{
	onCollision(SidesCollision::None);
}

void BangerBullet::changeState(BulletState state)
{
	bulletState = state;
	switch (state)
	{
	case BulletState::Fire:
	{
		anim->setAnimation(0, 1);
		this->setWidth(anim->getWidth());
		this->setHeight(anim->getHeight());
		break;
	}
	case BulletState::Burst:
	{
		animBurst->setAnimation(0, 10, 0.05, false);
		this->setWidth(animBurst->getWidth());
		this->setHeight(animBurst->getHeight());
		break;
	}
	default:break;
	}
}