#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Entity
{
public:
	virtual ~Entity() = default;
	Entity();

	enum SideCollisions
	{
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		None
	};

	enum Tag
	{
		RockMan,
		Enemy,
		EnemyBullet,
		RockManBullet,
		Brick,
		Static,
		BrickGoldNormal,
		BrickGoldEaten,
		TagNone
	};

	struct CollisionReturn
	{
		bool isCollision;
		RECT regionCollision;
	};

	virtual RECT getBound();

	virtual D3DXVECTOR3 getPosition() 						{ return { x, y, 0 }; }
	virtual void setPosition(float x, float y)				{ setPosition({ x, y }); }
	virtual void setPosition(D3DXVECTOR2 pos)				{ setPosition({ pos.x, pos.y, 0 }); }
	virtual void setPosition(D3DXVECTOR3 pos)				{ this->x = pos.x; this->y = pos.y; onSetPosition(pos); }

	virtual void addPosition(float x, float y)				{ addPosition({ x, y }); }
	virtual void addPosition(D3DXVECTOR2 pos)				{ addPosition({ pos.x, pos.y, 0 }); }
	virtual void addPosition(D3DXVECTOR3 pos)				{ setPosition(this->getPosition() + pos); }

	virtual void setWidth(int width)						{ this->width = width; }
	virtual int getWidth() 									{ return this->width; }

	virtual void setHeight(int height)						{ this->height = height; }
	virtual int getHeight() 								{ return this->height; }

	virtual float getVx() 									{ return this->vx; }
	virtual void setVx(float vx)							{ this->vx = vx; }
	virtual void addVx(float vx)							{ this->vx += vx; }

	virtual float getVy() 									{ return this->vy; }
	virtual void setVy(float vy)							{ this->vy = vy; }
	virtual void addVy(float vy)							{ this->vy += vy; }

	virtual void setDrawSprite(bool isDraw)					{ this->allowDrawSprite = isDraw; }
	virtual bool getDrawSprite() 							{ return this->allowDrawSprite; }

	virtual void setTag(Tag tags)							{ this->tag = tags; }
	virtual Tag getTag() 									{ return this->tag; }

	virtual void checkTimeCollision(float collisionTime, SideCollisions side, Entity *other);

	virtual void update(float dt);

	//Control collision
	//When entity collide, this function will be called
	virtual void onCollision(SideCollisions side);
	virtual void onCollision(Entity *obj);
	virtual void onNoCollisionWithBottom() { }

protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void onSetPosition(D3DXVECTOR3 pos) { }

	//vi tri tam position x va y
	float x, y;

	//phan toc vx, vy
	float vx, vy;

	//size cua entity
	float width, height;

	float collisionTimeMinX;
	float collisionTimeMinY;

	bool allowDrawSprite;	// allow to draw the sprite when the Camera contain Enemies

	SideCollisions sideX;
	SideCollisions sideY;
	Entity *entityX;
	Entity *entityY;
	Tag tag;
};
