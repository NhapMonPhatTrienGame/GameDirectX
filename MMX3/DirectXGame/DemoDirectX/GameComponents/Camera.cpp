#include "Camera.h"
#include "GameGlobal.h"


Camera::Camera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPositionWorld = D3DXVECTOR3(0, 0, 0);
}

void Camera::setPosition(float x, float y)
{
	setPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::setPosition(D3DXVECTOR3 pos)
{
	mPositionWorld = pos;
}

D3DXVECTOR2 Camera::getTrans() const
{
	return {
		GameGlobal::getWidth() / 2.0f - mPositionWorld.x,
		GameGlobal::getHeight() / 2.0f - mPositionWorld.y
	};
}

D3DXVECTOR3 Camera::getPosition() const
{
	return mPositionWorld;
}

RECT Camera::getBound() const
{
	RECT bound;

	bound.left = mPositionWorld.x - mWidth / 2.0f;
	bound.right = bound.left + mWidth;
	bound.top = mPositionWorld.y - mHeight / 2.0f;
	bound.bottom = bound.top + mHeight;

	return bound;
}

int Camera::getWidth() const
{
	return mWidth;
}

int Camera::getHeight() const
{
	return mHeight;
}
