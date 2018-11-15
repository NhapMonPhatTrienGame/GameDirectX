#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/Entity.h"

class GameCollision
{
public:
    
    GameCollision() = default;

    //Check collision Rect and Rect
    static Entity::CollisionReturn RectAndRect(RECT rect1, RECT rect2);

    static bool isCollide(RECT rect1, RECT rect2);

    //if Rectangle is big, it will error
    static Entity::SideCollisions getSideCollision(Entity *e1, Entity *e2);

    //Side collision of Entity
    static Entity::SideCollisions getSideCollision(Entity *e1, Entity::CollisionReturn data);

    //Check collision between Point and Rectangle
    static bool PointAndRectangle(float x, float y, RECT rect);

    //Check collision between Rectangle and Circle
    static bool RectangleAndCircle(RECT rect, int circle_x, int circle_y, int circleRadius);

	//Check collision
	static bool isCollision(RECT obj, RECT other);

	static D3DXVECTOR2 Distance(Entity *e1, Entity *e2, float dt);

	static RECT GetBoard(RECT object, D3DXVECTOR2 distance);

	//Axis-Aligned Bounding Box collision
	static float SweptAABB(RECT obj, RECT other, D3DXVECTOR2 distance, Entity::SideCollisions & sideCollision);

    ~GameCollision() = default;
};
