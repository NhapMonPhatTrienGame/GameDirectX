#pragma once
#include "../GameState.h"

class ClingState : public GameState
{
protected:
	float translateY;
	float speed, countPress;
	bool Pressed;
public:
	explicit ClingState(GamePlayer *gp, bool dash = false);
	ClingState() = default;
	~ClingState() override = default;


	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};