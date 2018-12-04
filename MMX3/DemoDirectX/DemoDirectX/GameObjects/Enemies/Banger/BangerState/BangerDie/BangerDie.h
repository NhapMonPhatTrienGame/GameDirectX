#ifndef BANGER_DIE_H
#define BANGER_DIE_H
#include "../BangerState.h"
#include "../../../../../GameDefines/GameDefine.h"

class BangerDie :public BangerState
{
private:
	float timeDie;

public:

	explicit BangerDie(Banger* banger)
		: BangerState(banger)
	{
		banger->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
		timeDie = 0;
		translateY = 25.0f;
	}

	~BangerDie() = default;
	::StateBanger getState() override;
	void update(float dt) override;

};
#endif
