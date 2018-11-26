#include "Entity.h"

Entity::Entity()
{
	tag = TagNone;
	vx = 0, vy = 0;
	collisionTimeMinX = 1.0f;
	collisionTimeMinY = 1.0f;
	sideX = None;
	sideY = None;
	allowDrawSprite = true;
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

void Entity::onCollision(SideCollisions side)
{
	vx = 0, vy = 0;
}

void Entity::onCollision(Entity* obj)
{
}

void Entity::update(float dt)
{
	if(sideX != None)
	{
		if(collisionTimeMinX == 0.0f)
		{
			if(getBound().bottom <= entityX->getBound().top || getBound().top >= entityX->getBound().bottom)
			{
				collisionTimeMinX = 1.0f;
				sideX = None;
			}
		}
		onCollision(sideX);
	}
	if(sideY != None)
	{
		if(collisionTimeMinY == 0.0f)
		{
			if(getBound().right <= entityY->getBound().left || getBound().left >= entityY->getBound().right)
			{
				collisionTimeMinY = 1.0f;
				sideY = None;
			}
		}
		onCollision(sideY);
	}

	x += vx * dt * collisionTimeMinX;
	y += vy * dt * collisionTimeMinY;
	collisionTimeMinX = 1.0f;
	collisionTimeMinY = 1.0f;
	sideX = None;
	sideY = None;
}

void Entity::checkTimeCollision(float collisionTime, SideCollisions side, Entity *other)
{
	switch (side)
	{
	case Left:
	case Right:
		{
			if (collisionTime > collisionTimeMinX)
				return;
			collisionTimeMinX = collisionTime;
			sideX = side;
			entityX = other;
			break;
		}
	case Top:
	case Bottom:
		{
			if (collisionTime > collisionTimeMinY)
				return;
			collisionTimeMinY = collisionTime;
			sideY = side;
			entityY = other;
			break;
		}

	default: break;
	}
}