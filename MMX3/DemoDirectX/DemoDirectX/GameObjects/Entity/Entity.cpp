#include "Entity.h"

Entity::Entity()
{
	tag = Tag::None;
	vx = 0, vy = 0;
	collision_time_minX = 1.0f;
	collision_time_minY = 1.0f;
	sideX = SidesCollision::None;
	sideY = SidesCollision::None;
	allowDraw = true;
	isDie = false;
}

RECT Entity::getBound()
{
	RECT bound;

	bound.left = x - width / 2.0f;
	bound.right = x + width / 2.0f;
	bound.top = y - height / 2.0f;
	bound.bottom = y + height / 2.0f;

	return bound;
}

void Entity::onCollision(SidesCollision side)
{
	vx = 0, vy = 0;
}

void Entity::onCollision(Entity* obj)
{
}

void Entity::update(float dt)
{
	if (sideX != SidesCollision::None)
	{
		if (collision_time_minY == 0.0f)
			if (getBound().bottom <= entityX->getBound().top ||
				getBound().top >= entityX->getBound().bottom)
			{
				collision_time_minX = 1.0f;
				sideX = SidesCollision::None;
			}
		onCollision(sideX);
	}
	if (sideY != SidesCollision::None)
	{
		if (collision_time_minX == 0.0f)
			if (getBound().right <= entityY->getBound().left ||
				getBound().left >= entityY->getBound().right)
			{
				collision_time_minY = 1.0f;
				sideY = SidesCollision::None;
			}
		onCollision(sideY);
	}
	//velocity = pixel / s
	x += vx * dt * collision_time_minX;
	y += vy * dt * collision_time_minY;
	collision_time_minX = 1.0f;
	collision_time_minY = 1.0f;
	sideX = SidesCollision::None;
	sideY = SidesCollision::None;
}

void Entity::checkTimeCollision(float collision_time, SidesCollision side, Entity *other)
{
	switch (side)
	{
	case SidesCollision::Left:
	case SidesCollision::Right:
	{
		if (collision_time >= collision_time_minX)
			return;
		collision_time_minX = collision_time;
		sideX = side;
		entityX = other;
		return;
		break;
	}
	case SidesCollision::Top:
	case SidesCollision::Bottom:
	{
		if (collision_time >= collision_time_minY)
			return;
		collision_time_minY = collision_time;
		sideY = side;
		entityY = other;
		return;
		break;
	}

	default:break;
	}
}