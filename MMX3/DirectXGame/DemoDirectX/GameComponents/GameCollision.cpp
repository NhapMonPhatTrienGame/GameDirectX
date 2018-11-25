#include "GameCollision.h"
#include <iostream>
using namespace std;


Entity::CollisionReturn GameCollision::collisionRectangle(RECT rect1, RECT rect2)
{
	Entity::CollisionReturn result = Entity::CollisionReturn();

	if (!isCheckCollision(rect1, rect2))
	{
		result.isCollision = false;
		return result;
	}

	result.isCollision = true;

	result.regionCollision.left = max(rect1.left, rect2.left);
	result.regionCollision.right = max(rect1.right, rect2.right);
	result.regionCollision.bottom = max(rect1.bottom, rect2.bottom);
	result.regionCollision.top = max(rect1.top, rect2.top);

	return result;
}

bool GameCollision::collisionPoint(float x, float y, RECT rect)
{
	return !(x < rect.left || x > rect.right || y < rect.top || y > rect.bottom);
}

bool GameCollision::collisionCircle(RECT rect, int circle_x, int circle_y, int circleRadius)
{
	int px = circle_x;
	int py = circle_y;

	if (px < rect.left)
		px = rect.left;
	else if (px > rect.right)
		px = rect.right;

	if (py > rect.bottom)
		py = rect.bottom;
	else if (py < rect.top)
		py = rect.top;

	const int dx = px - circle_x;
	const int dy = py - circle_y;

	return (dx * dx + dy * dy) <= circleRadius * circleRadius;
}

bool GameCollision::isCollisionRectangle(RECT obj, RECT other)
{
	return !(obj.left >= other.right || obj.right <= other.left || obj.top >= other.bottom || obj.bottom <= other.top);
}

D3DXVECTOR2 GameCollision::Distance(Entity* e1, Entity* e2, float dt)
{
	D3DXVECTOR2 distance;
	distance.x = (e1->getVx() - e2->getVx()) * dt;
	distance.y = (e1->getVy() - e2->getVy()) * dt;
	return distance;
}

RECT GameCollision::getBroad(RECT object, D3DXVECTOR2 distance)
{
	RECT broad = object;

	if (distance.x < 0)
		broad.left = object.left + distance.x;
	else if (distance.x > 0)
		broad.right = object.right + distance.x;

	if (distance.y > 0)
		broad.bottom = object.bottom + distance.y;
	else if (distance.y < 0)
		broad.top = object.top + distance.y;

	return broad;
}

float GameCollision::SweptAABB(RECT obj, RECT other, D3DXVECTOR2 distance, Entity::SideCollisions& sideCollision)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	if (distance.x > 0.0f)
	{
		dxEntry = other.left - obj.right;
		dxExit = other.right - obj.left;
	}
	else
	{
		dxEntry = other.right - obj.left;
		dxExit = other.left - obj.right;
	}

	if (distance.y > 0.0f)
	{
		dyEntry = other.top - obj.bottom;
		dyExit = other.bottom - obj.top;
	}
	else
	{
		dyEntry = other.bottom - obj.top;
		dyExit = other.top - obj.bottom;
	}

	float txEntry, txExit;
	float tyEntry, tyExit;

	if (distance.x == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / (distance.x);
		txExit = dxExit / (distance.x);
	}

	if (distance.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / (distance.y);
		tyExit = dyExit / (distance.y);
	}

	const float entryTime = max(txEntry, tyEntry);
	const float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		sideCollision = Entity::None;
		return 1.0f;
	}

	if (txEntry < tyEntry)
	{
		if (dyEntry < 0.0f)
		{
			sideCollision = Entity::Top;
		}
		else
		{
			sideCollision = Entity::Bottom;
		}
	}
	else
	{
		if (dxEntry < 0.0f)
		{
			sideCollision = Entity::Left;
		}
		else
		{
			sideCollision = Entity::Right;
		}
	}

	return entryTime;
}

bool GameCollision::isCheckCollision(RECT rect1, RECT rect2)
{
	return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.
		top);
}

Entity::SideCollisions GameCollision::getSideCollision(Entity* e1, Entity* e2)
{
	RECT rect1 = e1->getBound();
	RECT rect2 = e2->getBound();
	const float w = (e1->getWidth() + e2->getWidth()) / 2.0f;
	const float h = (e1->getHeight() + e2->getHeight()) / 2.0f;

	const float dx = e1->getPosition().x - e2->getPosition().y;
	const float dy = e1->getPosition().x - e2->getPosition().y;

	if (abs(int(dx)) <= w && abs(int(dy)) <= h)
	{
		// Has a collision
		const float wy = w * dy;
		const float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				//Collision Top e1
				return Entity::Top;
			}
			//Collision Right e1
			return Entity::Right;
		}
		if (wy > -hx)
		{
			//Collision Left e1
			return Entity::Left;
		}

		//Collision Bottom e1
		return Entity::Bottom;
	}
	//Don't collide
	return Entity::None;
}

Entity::SideCollisions GameCollision::getSideCollision(Entity* e1, Entity::CollisionReturn data)
{
	const float xCenter = data.regionCollision.left + (data.regionCollision.right - data.regionCollision.left) / 2.0f;
	const float yCenter = data.regionCollision.top + (data.regionCollision.bottom - data.regionCollision.top) / 2.0f;

	const D3DXVECTOR2 cCenter = D3DXVECTOR2(xCenter, yCenter);
	D3DXVECTOR2 eCenter;
	eCenter.x = e1->getPosition().x;
	eCenter.y = e1->getPosition().y;

	//Get centered vector between Entity and CollisionRect
	D3DXVECTOR2 vec = cCenter - eCenter;

	//Vector standardization
	D3DXVec2Normalize(&vec, &vec);

	/*
	- if Vector standardization has a y > 0 => Top side of Entity
	- if Vector standardization has a y < 0 => Bottom side of Entity
	- if Vector standardization has a x > 0 => Right side of Entity
	- if Vector standardization has a x < 0 => Left side of Entity
	*/

	if (vec.y < 0)
	{
		/*
		 * Top collision
		 * Get corner cosine if it is in the 70 -> 110 Top collision
		 */
		if (vec.x <= 0.35f && vec.x >= -0.35f)
		{
			return Entity::Top;
		}
		if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//The angle is between 35 -> 70 on the top - right side
			return Entity::TopRight;
		}
		if (vec.x >= 0.8f)
		{
			return Entity::Right;
		}
		if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//Top - Left collision
			return Entity::TopLeft;
		}

		return Entity::Left;
	}

	/*
	* Bottom collision
	* Get corner cosine if it is in the 70 -> 110 Bottom collision
	*/
	if (vec.x <= 0.35f && vec.x >= -0.35)
	{
		return Entity::Bottom;
	}
	if (vec.x > 0.35 && vec.x < 0.8)
	{
		//The angle is between 35 -> 70 on the Bottom - right side
		return Entity::BottomRight;
	}
	if (vec.x >= 0.8)
	{
		return Entity::Right;
	}
	if (vec.x < -0.35f && vec.x > -0.8f)
	{
		//Bottom - Left collision
		return Entity::BottomLeft;
	}

	return Entity::Left;
}
