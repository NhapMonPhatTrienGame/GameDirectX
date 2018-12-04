#pragma once
#include "GameObjects/Entity/Entity.h"
#include "GameComponents/Camera.h"
#include "GameComponents/Animation.h"

class GameMap;

class Box :
	public Entity
{
	Animation *anim;
	bool isBottom;
public:
	Box();
	~Box();

	void Draw(Camera *camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotateCenter = D3DXVECTOR2(), D3DCOLOR color = NULL);
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(SidesCollision side) override;
	void CheckCollision(GameMap *map, float dt);

	bool getBottom() const
	{
		return isBottom;
	}
};

