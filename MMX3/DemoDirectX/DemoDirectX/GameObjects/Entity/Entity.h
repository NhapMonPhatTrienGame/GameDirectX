#pragma once

#include <d3dx9.h>
#include <d3d9.h>

enum class SidesCollision
{
	Left,
	Right,
	Top,
	Bottom,
	None
};

enum class Tag
{
	RockMan,
	Enemy,
	EnemyBullet,
	RockManBullet,
	Brick,
	Static,
	BrickGoldNormal,
	BrickGoldEaten,
	None
};

class Entity
{
protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void onSetPosition(D3DXVECTOR3 pos) { }

	//vi tri tam position x va y
	float x, y;

	//phan toc vx, vy
	float vx, vy;

	//size cua entity
	float width, height;

	float collision_time_minX;
	float collision_time_minY;

	bool allowDraw;	// allow to draw the sprite when the Camera contain Enemies

	SidesCollision sideX;
	SidesCollision sideY;
	Entity *entityX;
	Entity *entityY;
	Tag tag;

	bool isReverse;
	bool isDie;

public:
	virtual ~Entity() = default;
	Entity();

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

	virtual void setDraw(bool isDraw)						{ this->allowDraw = isDraw; }
	virtual bool getDraw() 									{ return this->allowDraw; }

	virtual void setTag(Tag tags)							{ this->tag = tags; }
	virtual Tag getTag() 									{ return this->tag; }

	virtual void setReverse(bool reverse)					{ isReverse = reverse; }
	virtual bool getReverse()								{ return isReverse; }

	virtual void setDie(bool die)							{ isDie = die; }
	virtual bool getDie()									{ return isDie; }

	virtual void checkTimeCollision(float collisionTime, SidesCollision side, Entity *other);

	virtual void update(float dt);

	//Control collision
	//When entity collide, this function will be called
	virtual void onCollision(SidesCollision side);
	virtual void onCollision(Entity *obj);
	virtual void onNoCollisionWithBottom() { }

};
