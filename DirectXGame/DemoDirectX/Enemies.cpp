#include "Enemies.h"
#include "EnemiesStandState.h"
#include "EnemiesFallState.h"
#include "EnemiesJumpState.h"

Enemies::Enemies()
{
	Tag = Enemy;
	pEnemiesAnim = new Animation("Resources/Enemies/EnemiesSpriteSheet.png", 3, 4, 48, 48, 0.1f, D3DCOLOR_XRGB(100, 100, 100));
	setState(new EnemiesStandState(this));
}

Enemies::~Enemies()
{
	SAFE_DELETE(pState);
	SAFE_DELETE(pEnemiesAnim);
}

void Enemies::ChangeAnimation(EnemyState::EnemyStateName state)
{
	switch (state)
	{
	case EnemyState::Stand:
		pEnemiesAnim->setAnimation(0, 2, 0.15f);
		break;
	case EnemyState::Jump:
		pEnemiesAnim->setAnimation(1, 2, 0.15f, false);
		break;
	case EnemyState::Fall:
		pEnemiesAnim->setAnimation(1, 2, 0.15f, false);
		break;
	case EnemyState::Attack:
		pEnemiesAnim->setAnimation(2, 4, 0.15f, false);
		break;
	default: break;
	}

	this->setWidth(pEnemiesAnim->getWidth());
	this->setHeight(pEnemiesAnim->getHeight());
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
	rect.left = x - getWidth() / 2.0f;
	rect.right = rect.left + getWidth();
	rect.top = y - getHeight() / 2.0f;
	rect.bottom = rect.top + getHeight();
	return rect;
}

void Enemies::drawSprite(VECTOR3 pos, RECT rect, VECTOR2 scale, VECTOR2 translate, float angle, VECTOR2 rotationCenter, DX_COLOR transColor)
{
	pEnemiesAnim->setFlip(currentFlip);
	pEnemiesAnim->setPosition(getPosition());

	pEnemiesAnim->drawSprite(VECTOR3(x, y, 0), rect, scale, translate, angle, rotationCenter, transColor);
}

void Enemies::update(float gameTime)
{
	pEnemiesAnim->update(gameTime);
	if (pState)
		pState->update(gameTime);
	Entity::update(gameTime);
}

void Enemies::onCollision(SideCollisions side)
{
	if (pState)
		pState->onCollision(side);
}

void Enemies::onCollisionBottom()
{
	if (currentState == EnemyState::Fall || currentState == EnemyState::Jump || currentState == EnemyState::Attack)
		return;
	setState(new EnemiesFallState(this));
}
