#include "Enemies.h"
#include "EnemiesStandState.h"
#include "EnemiesFallState.h"

Enemies::Enemies()
{
	Tag = Enemy;
	pCurrentAnim = new Animation("Resources/Enemies/EnemiesSprite.png", 3, 4, 48, 48, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	currentFlip = true;
	allowDrawSprite = false;
	setState(new EnemiesStandState(this));
}

Enemies::~Enemies()
{
	SAFE_DELETE(pState);
	SAFE_DELETE(pCurrentAnim);
}

void Enemies::ChangeAnimation(EnemyState::EnemyStateName state)
{
	switch (state)
	{
	case EnemyState::Stand:
		pCurrentAnim->setAnimation(0, 2, 0.1);
		break;
	case EnemyState::Jump:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;
	case EnemyState::Fall:
		pCurrentAnim->setAnimation(1, 2, 0.15, false);
		break;
	case EnemyState::Attack:
		pCurrentAnim->setAnimation(2, 4, 0.15, false);
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
	ChangeAnimation(newState->getState());
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

void Enemies::drawSprite(Camera* pCamera, VECTOR3 pos, RECT rect, VECTOR2 scale, VECTOR2 translate, float angle, VECTOR2 rotationCenter, DX_COLOR transColor)
{
	if (!allowDrawSprite)
		return;

	pCurrentAnim->setFlip(currentFlip);
	pCurrentAnim->setPosition(getPosition());

	if (pCamera)
	{
		pCurrentAnim->drawSprite(pCurrentAnim->getPosition(), rect, scale, pCamera->getTrans(), angle, rotationCenter, transColor);
	}
	else
		pCurrentAnim->drawSprite(D3DXVECTOR3(x, y, 0));
}

void Enemies::update(float gameTime)
{
	onCollisionBottom();
	pCurrentAnim->update(gameTime);

	Entity::update(gameTime);

	if (pState)
		pState->update(gameTime);
	
}

void Enemies::onCollision(SideCollisions side)
{
	if (pState)
		pState->onCollision(side);
}

void Enemies::onCollisionBottom()
{
	if (sideY != Bottom)
	{
		switch (currentState)
		{
		case EnemyState::Stand:
		case EnemyState::Attack:
			setState(new EnemiesFallState(this));
			break;

		default:
			break;
		}
	}
}