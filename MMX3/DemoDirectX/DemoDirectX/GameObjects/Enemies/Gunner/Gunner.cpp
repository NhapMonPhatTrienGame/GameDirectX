#include "Gunner.h"
#include "../../../GameDefines/GameDefine.h"
#include "GunnerState/GunnerFall/GunnerFall.h"
#include "../../Player/GamePlayer.h"
#include "GunnerState/GunnerDie/GunnerDie.h"
#include "../../../GameComponents/GameCollision.h"

Gunner::Gunner()
{
	tag = Tag::Enemy;
	anim = new Animation(Define::HEAD_GUNNER_SPRITE, 4, 4, 51, 45, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	isReverse = false;
	allowDraw = true;
	isDie = false;
	HP = 10;
	currentState = StateGunner::None;
	setState(new GunnerFall(this));
}

Gunner::~Gunner()
{
	delete anim;
	for (auto& bullet : listGunnerBullet)
		delete bullet;
	listGunnerBullet.clear();
}

RECT Gunner::getBound()
{
	RECT rect;
	rect.left = x - 25;
	rect.right = x + 25;
	rect.top = y - 21;
	rect.bottom = y + 45 / 2.0f;
	return rect;
}

void Gunner::update(float dt)
{
	onNoCollisionWithBottom();

	for (auto& bullet : listGunnerBullet)
		bullet->update(dt);

	if (!allowDraw)
		return;

	anim->update(dt);
	Entity::update(dt);

	if (pGunnerState)
		pGunnerState->update(dt);
}

void Gunner::onCollision(SidesCollision side)
{
	if(pGunnerState)
		pGunnerState->onCollision(side);
}

void Gunner::onCollision(Entity* obj)
{
	if(obj->getTag() == Tag::RockManBullet && !isDie)
	{
		HP -= 1.0f;
		if (HP <= 0)
			setState(new GunnerDie(this));
	}
}

void Gunner::onNoCollisionWithBottom()
{
	if(sideY != SidesCollision::Bottom)
	{
		switch (currentState)
		{
		case StateGunner::Stand:
		case StateGunner::Attack:
		case StateGunner::AttackRocket:
		case StateGunner::AttackBullet:
			setState(new GunnerFall(this));
			break;
		default: break;
		}
	}
}

void Gunner::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR color)
{
	if(!isDie)
	{
		if (!GameCollision::isCollision(this->getBound(), camera->getBound()))
			allowDraw = false;
		else
			allowDraw = true;
	}

	for (auto& bullet : listGunnerBullet)
		bullet->draw(camera);

	if (!allowDraw)
		return;

	anim->setPosition(this->getPosition());
	anim->setReverse(isReverse);

	if (camera)
		anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		anim->draw(anim->getPosition());
}

void Gunner::changeAnimation(StateGunner stateName)
{
	isDie = false;

	switch (stateName)
	{
	case StateGunner::Stand:
		anim->setAnimation(0, 1);
		break;
	case StateGunner::Attack:
		anim->setAnimation(2, 3, 0.15, false);
		break;
	case StateGunner::AttackRocket:
		anim->setAnimation(1, 3, 0.15, false);
		break;
	case StateGunner::AttackBullet:
		anim->setAnimation(0, 1);
		break;
	case StateGunner::Fall:
		anim->setAnimation(0, 1);
		break;
	case StateGunner::Die:
		anim->setAnimation(3, 1, 0.1);
		isDie = true;
		break;
	default: break;
	}

	this->setWidth(anim->getWidth());
	this->setHeight(anim->getHeight());
}

void Gunner::setState(GunnerState* state)
{
	if (currentState == state->getState())
		return;

	delete pGunnerState;
	pGunnerState = state;
	currentState = state->getState();
	changeAnimation(state->getState());
}
