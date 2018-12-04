#pragma once
#include "../BangerState.h"

class BangerAttack :
	public BangerState
{
protected:
	float timeAttack;
	int count;

public:
	explicit BangerAttack(Banger *e);
	~BangerAttack() = default;

	void update(float dt) override;
	::StateBanger getState() override;
};
