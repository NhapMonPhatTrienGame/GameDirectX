#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	tag = Tag::EnemyBullet;
	anim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1);
	animBurst = new Animation(Define::BURST, 1, 10, 50, 46, 0.1);
	GunnerBullet::changeState(BulletState::Fire);
	isReverse = true;
	isBurst = false;
	bulletX = 25.0f;
	timeFire = 0.0f;
}

GunnerBullet::~GunnerBullet()
{
	delete anim;
	delete animBurst;
}

RECT GunnerBullet::getBound()
{
	RECT r = RECT();

	switch (bulletState)
	{
	case BulletState::Fire:
		r.left = x - 10;
		r.right = x + 13;
		r.top = y - 3;
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

void GunnerBullet::newBullet(float bx, float by, bool direction)
{
	x = bx;
	y = by;

	if (!direction)
	{
		setReverse(false);
		setVx(-80);
		setBulletX(-25.0f);
	}
	else
	{
		setReverse(true);
		setVx(80);
		setBulletX(25.0f);
	}

	changeState(BulletState::Fire);
	isBurst = false;
	allowDraw = true;
}

void GunnerBullet::update(float dt)
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
	else if (anim->getPause() || animBurst->getPause())
		allowDraw = false;

	if (bulletState == BulletState::Burst)
		animBurst->update(dt);
	else
		anim->update(dt);

	Entity::update(dt);
}

void GunnerBullet::onCollision(SidesCollision side)
{
	vx = 0;
	vy = 0;
	isBurst = true;
	changeState(BulletState::Burst);
}

void GunnerBullet::onCollision(Entity* obj)
{
	onCollision(SidesCollision::None);
}

void GunnerBullet::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!GameCollision::isCollision(camera->getBound(), this->getBound()))
	{
		allowDraw = false;
		isBurst = true;
	}

	if (!allowDraw)
		return;

	switch (bulletState)
	{
	case BulletState::Fire:
	{
		anim->setReverse(isReverse);
		anim->setPosition(this->getPosition());
		if (camera)
			anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			anim->draw(anim->getPosition());
		break;
	}
	case BulletState::Burst:
	{
		animBurst->setPosition(this->getPosition());
		if (camera)
			animBurst->draw(animBurst->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			animBurst->draw(animBurst->getPosition());
	}
	default:break;
	}
}

void GunnerBullet::changeState(BulletState state)
{
	bulletState = state;

	switch (state)
	{
	case BulletState::Fire:
	{
		anim->setAnimation(0, 2);
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
