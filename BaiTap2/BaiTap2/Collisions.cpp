#include "Collisions.h"
#include <iostream>
#include <windows.h>

Collisions::Collisions()
{}

Collisions::~Collisions()
{}

BOX Collisions::GetSweptBroadphaseBox(BOX b)
{
	BOX broadphasebox = BOX();

	broadphasebox.x = b._velocityX > 0 ? b.x : b.x + b._velocityX;
	broadphasebox.y = b._velocityY > 0 ? b.y : b.y + b._velocityY;
	broadphasebox.width = b._velocityX > 0 ? b._velocityX + b.width : b.width - b._velocityX;
	broadphasebox.height = b._velocityY > 0 ? b._velocityY + b.height : b.height - b._velocityY;

	return broadphasebox;
}

bool Collisions::isCollision(BOX b1, BOX b2)
{
	return !(b1.x + b1.width < b2.x || b1.x > b2.x + b2.width || b1.y + b1.height < b2.y || b1.y > b2.y + b2.height);
}

float Collisions::SweptAABB(BOX b1, BOX b2, float& normalx, float& normaly, float dt)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	if (b1._velocityX > 0.0f)
	{
		dxEntry = b2.x - (b1.x + b1.width);
		dxExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		dxEntry = (b2.x + b2.width) - b1.x;
		dxExit = b2.x - (b1.x + b1.width);
	}

	if (b1._velocityY > 0.0f)
	{
		dyEntry = b2.y - (b1.y + b1.height);
		dyExit = (b2.y + b2.height) - b1.y;
	}
	else
	{
		dyEntry = (b2.y + b2.height) - b1.y;
		dyExit = b2.y - (b1.y + b1.height);
	}

	float txEntry, txExit;
	float tyEntry, tyExit;

	if (b1._velocityX == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / (b1._velocityX*dt);//thêm dt chỗ này lấy tỉ lệ nè, mà khoảng cách chia vận tốc sai. Phải là khoảng cách chia khoảng cách đi được trong farm đó
		txExit = dxExit / (b1._velocityX*dt);//
	}

	if (b1._velocityY == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / (b1._velocityY*dt);//thêm dt
		tyExit = dyExit / (b1._velocityY*dt);//
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	if (txEntry > tyEntry)
	{
		if (dxEntry < 0.0f)
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else
	{
		if (dyEntry < 0.0f)
		{
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else
		{
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}

	return entryTime;
}
