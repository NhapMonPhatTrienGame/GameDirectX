#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	tag = Tag::EnemyBullet;
	anim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	animBurst = new Animation(Define::BURST, 1, 10, 50, 46);

	HelitBullet::changeState(BulletState::Fire);

	isReverse = false;
	isBurst = false;
	allowDraw = true;
	bulletX = 25.0f;
}

HelitBullet::~HelitBullet()
{
	delete anim;
	delete animBurst;
}

void HelitBullet::newBullet(float bx, float by, bool direction)
{
	x = bx;
	y = by;

	if (direction)
	{
		setReverse(true);
		setVx(80);
		setBulletX(25.0f);
	}
	else
	{
		setReverse(false);
		setVx(-80);
		setBulletX(-25.0f);
	}

	changeState(BulletState::Fire);
	isBurst = false;
	allowDraw = true;
}

RECT HelitBullet::getBound()
{
	RECT r = RECT();

	switch (bulletState)
	{
	case BulletState::Fire:
	{
		r.left = x - 7;
		r.right = x + 8;
		r.top = y - 5;
		r.bottom = y + 5;
		break;
	}
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

void HelitBullet::update(float dt)
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

void HelitBullet::onCollision(SidesCollision side)
{
	vx = 0;
	vy = 0;
	isBurst = true;
	changeState(BulletState::Burst);
}

void HelitBullet::onCollision(Entity* obj)
{
	onCollision(SidesCollision::None);
}

void HelitBullet::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if (!GameCollision::isCollision(camera->getBound(), getBound()))
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
		break;
	}
	default:break;
	}
}

void HelitBullet::changeState(BulletState state)
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
