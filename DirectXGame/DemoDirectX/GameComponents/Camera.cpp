#include "Camera.h"


Camera::Camera() = default;

Camera::Camera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPositionWorld = D3DXVECTOR3(0, 0, 0);
}

Camera::~Camera() = default;

void Camera::setPosition(float x, float y)
{
	setPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::setPosition(D3DXVECTOR3 pos)
{
	mPositionWorld = pos;
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
