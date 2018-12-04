#include "GameCollision.h"
#include <iostream>
using namespace std;


bool GameCollision::pointCollision(float x, float y, RECT rect)
{
	return !(x < rect.left || x > rect.right || y < rect.top || y > rect.bottom);
}

bool GameCollision::circleCollision(RECT rect, int circle_x, int circle_y, int circleRadius)
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

bool GameCollision::intersectRect(RECT obj, RECT other)
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

float GameCollision::SweptAABB(RECT obj, RECT other, D3DXVECTOR2 distance, SidesCollision& sideCollision)
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
		sideCollision = SidesCollision::None;
		return 1.0f;
	}

	if (txEntry < tyEntry)
	{
		if (dyEntry < 0.0f)
		{
			sideCollision = SidesCollision::Top;
		}
		else
		{
			sideCollision = SidesCollision::Bottom;
		}
	}
	else
	{
		if (dxEntry < 0.0f)
		{
			sideCollision = SidesCollision::Left;
		}
		else
		{
			sideCollision = SidesCollision::Right;
		}
	}

	return entryTime;
}

bool GameCollision::isCollision(RECT rect1, RECT rect2)
{
	return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.
		top);
}