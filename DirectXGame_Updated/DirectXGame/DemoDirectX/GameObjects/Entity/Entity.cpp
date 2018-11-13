#include "Entity.h"

Entity::Entity()
{
    Tag = Unknown;
	vx = 0, vy = 0;
	collision_time_min = 1.0f;
}

RECT Entity::getBound()
{
    RECT bound;

    bound.left = x - width / 2;
    bound.right = x + width / 2;
    bound.top = y - height / 2;
    bound.bottom = y + height / 2;

    return bound;
}

void Entity::OnCollision(Entity::SideCollisions side)
{
    vx = 0, vy = 0;
}

void Entity::Update(float dt)
{
    //velocity = pixel / s
    x += vx * dt * collision_time_min;
    y += vy * dt;
	collision_time_min = 1.0f;
}

void Entity::UpdateColision(float collision_time, SideCollisions side, float dt)
{
	switch (side)
	{
		case Entity::Left:
		case Entity::Right:
		{
			if (collision_time > collision_time_min)
				return;
			collision_time_min = collision_time;
			vx = 0;
			break;
		}
		case Entity::Top:
		case Entity::Bottom:
		{
			y += vy * dt * collision_time;
			vy = 0;
			break;
		}

		default:break;
	}
}

void Entity::onSetPosition(D3DXVECTOR3 pos)
{}

D3DXVECTOR3 Entity::getPosition()
{
	return { x, y, 0 };
}
void Entity::setPosition(float x, float y)
{
	const auto pos = D3DXVECTOR2(x, y);
    setPosition(pos);
}
void Entity::setPosition(D3DXVECTOR2 pos)
{
	const auto position = D3DXVECTOR3(pos);
    setPosition(position);
}
void Entity::setPosition(D3DXVECTOR3 pos)
{
    this->x = pos.x;
    this->y = pos.y; 
    onSetPosition(pos);
}
void Entity::addPosition(float x, float y)
{
	const auto pos = D3DXVECTOR2(x, y);
    addPosition(pos);
}
void Entity::addPosition(D3DXVECTOR2 pos)
{
	const auto position = D3DXVECTOR3(pos);
	addPosition(position);
}
void Entity::addPosition(D3DXVECTOR3 pos)
{
    this->setPosition(this->getPosition() + pos);
}

void Entity::setWidth(int width)
{
    this->width = width;
}
int Entity::getWidth()
{
    return width;
}

void Entity::setHeight(int height)
{
    this->height = height;
}
int Entity::getHeight()
{
    return height;
}

float Entity::getVx()
{
    return vx;
}
void Entity::setVx(float vx)
{
    this->vx = vx;
}
void Entity::addVx(float vx)
{
    this->vx += vx;
}

float Entity::getVy()
{
    return vy;
}
void Entity::setVy(float vy)
{
    this->vy = vy;
}
void Entity::addVy(float vy)
{
    this->vy += vy;
}