#include "Box.h"
#include "GameDefines/GameDefine.h"
#include "GameComponents/GameCollision.h"
#include "GameComponents/GameMap.h"


Box::Box()
{
	anim = new Animation(Define::BOX, 1, 1, 36, 36);
	Entity::setWidth(anim->getWidth());
	Entity::setHeight(anim->getHeight());

	allowDraw = true;
	isBottom = false;
}


Box::~Box()
{
	delete anim;
}

void Box::Draw(Camera* camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotateCenter, D3DCOLOR color)
{
	if (!allowDraw) return;

	anim->setPosition(getPosition());
	if (camera) anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
	else anim->draw(anim->getPosition());
}

RECT Box::getBound()
{
	RECT r = RECT();
	r.left = x - 36 / 2.0f;
	r.right = r.left + 36;
	r.top = y - 36 / 2.0f;
	r.bottom = r.top + 36;
	return r;
}

void Box::update(float dt)
{
	if (!allowDraw) return;

	anim->update(dt);
	Entity::update(dt);
}

void Box::onCollision(SidesCollision side)
{
	if (SidesCollision::Bottom == side) isBottom = true;
}

void Box::CheckCollision(GameMap* map, float dt)
{
	std::vector<Entity*> objectsCollide;
	map->getQuadTree()->getEntitiesCollideAble(objectsCollide, this);

	for (auto& i : objectsCollide)
	{
		D3DXVECTOR2 distance = GameCollision::Distance(this, i, dt);
		RECT broad = GameCollision::getBroad(this->getBound(), distance);

		if (GameCollision::isCollision(broad, i->getBound()))
		{
			SidesCollision other_with_entity;
			float collision_time = GameCollision::SweptAABB(this->getBound(), i->getBound(), distance, other_with_entity);

			if (collision_time < 1.0f)
			{
				this->checkTimeCollision(collision_time, other_with_entity, i);
			}
		}
	}
}
