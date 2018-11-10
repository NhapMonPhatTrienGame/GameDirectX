#include "Camera.h"


Camera::Camera()
{}

Camera::Camera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPositionWorld = D3DXVECTOR3(0, 0, 0);
}

Camera::~Camera()
{}

void Camera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	mPositionWorld = pos;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return mPositionWorld;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = mPositionWorld.x - mWidth / 2.0f;
	bound.right = bound.left + mWidth;
	bound.top = mPositionWorld.y - mHeight / 2.0f;
	bound.bottom = bound.top + mHeight;

	return bound;
}

int Camera::GetWidth()
{
	return mWidth;
}

int Camera::GetHeight()
{
	return mHeight;
}