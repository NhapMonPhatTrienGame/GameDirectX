#ifndef __SCENE__
#define __SCENE__
#include <d3d9.h>

class Scene
{
protected:
	D3DCOLOR mBackColor;

public:
	Scene();
	virtual ~Scene() = default;

	virtual void Update(float dt);
    virtual void LoadContent();
    virtual void Draw();

    virtual void OnKeyDown(int keyCode);
    virtual void OnKeyUp(int keyCode);

	virtual void OnMouseDown(float x, float y);

	D3DCOLOR getBackColor() const;
};

#endif

