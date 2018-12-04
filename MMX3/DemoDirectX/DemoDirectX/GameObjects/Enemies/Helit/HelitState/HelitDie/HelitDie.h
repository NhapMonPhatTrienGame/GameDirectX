#ifndef HELIT_DIE_H
#define HELIT_DIE_H
#include "../HelitState.h"

class HelitDie :public HelitState
{
protected:
	float timeDie;

public:
	explicit HelitDie(Helit* helit);
	~HelitDie() = default;
	::StateHelit getState() override;
	void update(float dt) override;

};

#endif
