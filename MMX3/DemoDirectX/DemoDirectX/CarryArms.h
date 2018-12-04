#pragma once
#include "GameObjects/Entity/Entity.h"
#include "GameComponents/Animation.h"
#include "GameComponents/Camera.h"
#include "Box.h"

enum class CarryArmsState
{
	Stand,
	MoveDown,
	MoveUp,
	EventMoveUp,
	EventMoveUpTwice,
	None
};

class CarryArms :public Entity
{
	Box *box;
	Animation *anim;
	CarryArmsState currentState;
	float distance;
	float timeMoveDown;
	float timeMoveUp;

public:
	CarryArms();
	~CarryArms();

	void draw(Camera *camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotateCenter = D3DXVECTOR2(), D3DCOLOR color = NULL);
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(Entity* obj) override;
	void CheckCollision(GameMap *map, float dt) const;
	void setState(CarryArmsState state);

	void Stand(float dt);
	void MoveDown(float dt);
	void MoveUp(float dt);
	void EventMoveUp(float dt);
	void EventMoveUpTwice(float dt);

	void ManageState(float dt);
};
