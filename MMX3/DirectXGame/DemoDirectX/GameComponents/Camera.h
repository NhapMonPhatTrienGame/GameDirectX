#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
	int mWidth,
	    mHeight;

	D3DXVECTOR3 mPositionWorld;

public:
	Camera();
	Camera(int width, int height);

	//center of camera
	D3DXVECTOR3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(D3DXVECTOR3 pos);
	D3DXVECTOR2 getTrans();

	int getWidth() const;
	int getHeight() const;

	RECT getBound() const;

	~Camera();
};
