#ifndef _COLLISION_H
#define _COLLISION_H

typedef struct
{
	float _velocityX;
	float _velocityY;

	float x;
	float y;

	float width;
	float height;
} BOX;

class Collisions
{
	
public:

	Collisions();

	~Collisions();

	BOX GetSweptBroadphaseBox(BOX b);

	bool isCollision(BOX b1, BOX b2);

	float SweptAABB(BOX object, BOX other, float &normalx, float &normaly, float dt);
};

#endif
