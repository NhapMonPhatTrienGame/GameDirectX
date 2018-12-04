#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/Entity.h"

class GameCollision
{
public:
	static bool isCollision(RECT rect1, RECT rect2);

	//Check collision between Point and Rectangle
	static bool pointCollision(float x, float y, RECT rect);

	//Check collision between Rectangle and Circle
	static bool circleCollision(RECT rect, int circle_x, int circle_y, int circleRadius);

	//Checking intersectRect
	static bool intersectRect(RECT obj, RECT other);

	static D3DXVECTOR2 Distance(Entity* e1, Entity* e2, float dt);

	static RECT getBroad(RECT object, D3DXVECTOR2 distance);

	//Axis-Aligned Bounding Box collision
	static float SweptAABB(RECT obj, RECT other, D3DXVECTOR2 distance, ::SidesCollision& sideCollision);
};
