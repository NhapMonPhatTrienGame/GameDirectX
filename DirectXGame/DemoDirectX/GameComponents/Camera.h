#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
	int             mWidth,
					mHeight;

	D3DXVECTOR3     mPositionWorld;

public:
	Camera();
    Camera(int width, int height);

    //center of camera
	D3DXVECTOR3 GetPosition();
    void SetPosition(float x, float y);
    void SetPosition(D3DXVECTOR3 pos);


    int GetWidth();
    int GetHeight();

    RECT GetBound();

    ~Camera();

};

