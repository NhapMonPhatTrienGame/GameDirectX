#ifndef HELIT_ATTACK_H
#define HELIT_ATTACK_H
#include "../HelitState.h"

class HelitAttack :public HelitState
{
private:
	float count;

public:
	explicit HelitAttack(Helit* helit);
	~HelitAttack() = default;
	::StateHelit getState() override;
	void update(float dt) override;

};
#endif