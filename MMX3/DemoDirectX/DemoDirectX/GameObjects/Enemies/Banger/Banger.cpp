#include "Banger.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "BangerState/BangerFall/BangerFall.h"
#include "BangerState/BangerDie/BangerDie.h"
#include "../../../GameComponents/GameCollision.h"

Banger::Banger()
{
	tag = Tag::Enemy;
	pAnimationDie = new Animation(Define::BANGER_DIE, 1, 1, 85, 23, D3DCOLOR_XRGB(100, 100, 100));
	pCurrentAnim = new Animation(Define::NOTOR_BANGER_SPRITE, 3, 4, 48, 48, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	HP = 10;
	isReverse = true;
	allowDraw = true;
	isDie = false;
	currentState = StateBanger::None;
	setState(new BangerFall(this));
}

Banger::~Banger()
{
	delete pState;
	delete pCurrentAnim;
	delete pAnimationDie;
	for (auto& bullet : ListBullet)
		delete bullet;
	ListBullet.clear();
}

void Banger::changeAnimation(StateBanger state)
{
	isDie = false;
	switch (state)
	{
	case StateBanger::Stand:
		pCurrentAnim->setAnimation(0, 2, 0.1);
		break;
	case StateBanger::Jump:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;
	case StateBanger::Fall:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;
	case StateBanger::Attack:
		pCurrentAnim->setAnimation(2, 3, 0.15, false);
		break;
	case StateBanger::Die:
		pAnimationDie->setAnimation(0, 1);
		isDie = true;
		break;
	default: break;
	}

	switch(state)
	{
	case StateBanger::Die:
		this->setWidth(pAnimationDie->getWidth());
		this->setHeight(pAnimationDie->getHeight());
		break;
	default:
		this->setWidth(pCurrentAnim->getWidth());
		this->setHeight(pCurrentAnim->getHeight());
		break;
	}
}


void Banger::setState(BangerState* newState)
{
	if (currentState == newState->getState())
		return;

	delete pState;
	pState = newState;
	currentState = newState->getState();
	changeAnimation(newState->getState());
}

RECT Banger::getBound()
{
	RECT r;
	r.left = x - 18;
	r.right = x + 18;
	r.top = y - 22;
	r.bottom = y + 48 / 2.0f;

	return r;
}

void Banger::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR transColor)
{
	if(!isDie)
	{
		if (!GameCollision::isCollision(this->getBound(), camera->getBound()))
			allowDraw = false;
		else
			allowDraw = true;
	}

	for (auto& Bullet : ListBullet)
		Bullet->draw(camera);

	if (!allowDraw)
		return;
	
	if(isDie)
	{
		pAnimationDie->setPosition(getPosition());

		if (camera)
			pAnimationDie->draw(pAnimationDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
		else
			pAnimationDie->draw(pAnimationDie->getPosition());
	}
	else
	{
		pCurrentAnim->setReverse(isReverse);
		pCurrentAnim->setPosition(getPosition());

		if (camera)
			pCurrentAnim->draw(pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
		else
			pCurrentAnim->draw(pCurrentAnim->getPosition());
	}
}


void Banger::update(float gameTime)
{
	onNoCollisionWithBottom();

	for (auto& Bullet : ListBullet)
		Bullet->update(gameTime);

	if (!allowDraw)
		return;

	Entity::update(gameTime);
	if(isDie)
		pAnimationDie->update(gameTime);
	else
		pCurrentAnim->update(gameTime);

	if (pState)
		pState->update(gameTime);
}

void Banger::onCollision(SidesCollision side)
{
	if (pState)
		pState->onCollision(side);
}

void Banger::onCollision(Entity* obj)
{
	if (obj->getTag() == Tag::RockManBullet && !isDie)
	{
		HP -= 1.0f;
		if (HP <= 0)
			this->setState(new BangerDie(this));
	}
}

void Banger::onNoCollisionWithBottom()
{
	if (sideY != SidesCollision::Bottom)
	{
		switch (currentState)
		{
		case StateBanger::Stand: case StateBanger::Attack:
			setState(new BangerFall(this));
			break;
		default:break;
		}
	}
}
