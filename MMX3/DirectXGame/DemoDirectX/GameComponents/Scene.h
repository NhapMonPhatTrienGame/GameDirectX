#ifndef __SCENE__
#define __SCENE__
#include <d3d9.h>

class Scene
{
protected:
	D3DCOLOR mBackColor;

public:
	virtual ~Scene() = default;
	Scene();

	virtual void update(float dt);
	virtual void draw();

	virtual void onKeyDown(int keyCode);
	virtual void onKeyUp(int keyCode);

	virtual void onMouseDown(float x, float y);

	D3DCOLOR getBackColor() const;
};

#endif
