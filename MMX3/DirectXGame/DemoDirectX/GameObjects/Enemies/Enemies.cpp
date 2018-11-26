#include "Enemies.h"
#include "../../GameDefines/GameDefine.h"
#include "EnemiesState/FallState/EnemiesFallState.h"
#include "../../GameComponents/Camera.h"

Enemies::Enemies()
{
	tag = Enemy;
	pCurrentAnim = new Animation(Define::ENEMIES_SPRITE_SHEET, 3, 4, 48, 48, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	currentFlip = true;
	allowDrawSprite = false;
	setState(new EnemiesFallState(this));
}

Enemies::~Enemies()
{
	SAFE_DELETE(pState);
	SAFE_DELETE(pCurrentAnim);
	for (auto& bullet : ListBullet)
		delete bullet;
}

void Enemies::changeAnimation(StateName state)
{
	switch (state)
	{
	case StateName::Stand:
		pCurrentAnim->setAnimation(0, 2, 0.1);
		break;
	case StateName::Jump:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;
	case StateName::Fall:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;
	case StateName::Attack:
		pCurrentAnim->setAnimation(2, 3, 0.15, false);
		break;
	default: break;
	}

	this->setWidth(pCurrentAnim->getWidth());
	this->setHeight(pCurrentAnim->getHeight());
}


void Enemies::setState(EnemiesState* newState)
{
	if (currentState == newState->getState())
		return;

	SAFE_DELETE(pState);
	pState = newState;
	changeAnimation(newState->getState());
	currentState = newState->getState();
}

RECT Enemies::getBound()
{
	RECT rect;
	rect.left = x - 18;
	rect.right = x + 18;
	rect.top = y - 22;
	rect.bottom = y + 48 / 2.0f;

	return rect;
}

void Enemies::drawSprite(Camera* camera, RECT rect, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotationCenter,
	D3DCOLOR transColor)
{
	for (auto& Bullet : ListBullet)
		Bullet->drawSprite(camera);

	if (!allowDrawSprite)
		return;

	pCurrentAnim->setFlip(currentFlip);
	pCurrentAnim->setPosition(getPosition());

	if (camera)
		pCurrentAnim->drawSprite(pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, transColor);
	else
		pCurrentAnim->drawSprite(pCurrentAnim->getPosition());
}


void Enemies::update(float gameTime)
{
	onNoCollisionWithBottom();

	for (auto& Bullet : ListBullet)
		Bullet->update(gameTime);
	
	if (!allowDrawSprite)
		return;

	Entity::update(gameTime);
	pCurrentAnim->update(gameTime);

	if (pState)
		pState->update(gameTime);
}

void Enemies::onCollision(SideCollisions side)
{
	if (pState)
		pState->onCollision(side);
}

void Enemies::onNoCollisionWithBottom()
{
	if(sideY != Bottom)
	{
		switch(currentState)
		{
		case Stand:
		case Attack:
			setState(new EnemiesFallState(this));
			break;
		default:break;
		}
	}
}
