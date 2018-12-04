#include "Helit.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "HelitState/HelitDie/HelitDie.h"
#include "HelitState/HelitStand/HelitStand.h"
#include "../../../GameComponents/GameCollision.h"

Helit::Helit()
{
	tag = Tag::Enemy;
	anim = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1, D3DCOLOR_XRGB(100, 100, 100));
	animDie = new Animation(Define::HELIT_DIE, 1, 1, 64, 23, 0.1, D3DCOLOR_XRGB(100, 100, 100));
	isReverse = false;
	isDie = false;
	allowDraw = true;
	HP = 10;
	currentState = StateHelit::None;
	setState(new HelitStand(this));
}


Helit::~Helit()
{
	delete pState;
	delete anim;
	delete animDie;
	for (auto& bullet : listBullet)
		delete bullet;
	listBullet.clear();
}

RECT Helit::getBound()
{
	RECT r;
	r.left = x - 19;
	r.right = x + 19;
	r.top = y - 18;
	r.bottom = y + 37 / 2.0f;
	return r;
}

void Helit::update(float dt)
{
	for (auto& bullet : listBullet)
		bullet->update(dt);

	if (!allowDraw)
		return;

	Entity::update(dt);

	if (isDie)
		animDie->update(dt);
	else
		anim->update(dt);

	if (pState)
		pState->update(dt);
}

void Helit::onCollision(Entity* obj)
{
	if (obj->getTag() == Tag::RockManBullet && !isDie)
	{
		HP -= 1.0f;
		if (HP <= 0)
			setState(new HelitDie(this));
	}
}

void Helit::draw(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR color)
{
	if (!isDie)
	{
		if (!GameCollision::isCollision(this->getBound(), camera->getBound()))
			allowDraw = false;
		else
			allowDraw = true;
	}

	for (auto& bullet : listBullet)
		bullet->draw(camera);

	if (!allowDraw)
		return;

	if (isDie)
	{
		animDie->setPosition(this->getPosition());

		if (camera)
			animDie->draw(animDie->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			animDie->draw(animDie->getPosition());
	}
	else
	{
		anim->setReverse(isReverse);
		anim->setPosition(this->getPosition());

		if (camera)
			anim->draw(anim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			anim->draw(anim->getPosition());
	}
}

void Helit::setState(HelitState* newState)
{
	if (currentState == newState->getState())
		return;

	delete pState;
	pState = newState;
	currentState = newState->getState();
	changeAnimation(newState->getState());
}

void Helit::changeAnimation(StateHelit state)
{
	isDie = false;

	switch (state)
	{
	case StateHelit::Stand:
		anim->setAnimation(0, 4, 0.05f);
		anim->setFrames(39, 36);
		break;
	case StateHelit::Attack:
		anim->setAnimation(1, 4, 0.05f);
		anim->setFrames(39, 36);
		break;
	case StateHelit::Die:
		animDie->setAnimation(0, 1);
		isDie = true;
		break;
	default: break;
	}

	switch (state)
	{
	case StateHelit::Die:
		this->setWidth(animDie->getWidth());
		this->setHeight(animDie->getHeight());
		break;
	default:
		this->setWidth(anim->getWidth());
		this->setHeight(anim->getHeight());
		break;
	}
}