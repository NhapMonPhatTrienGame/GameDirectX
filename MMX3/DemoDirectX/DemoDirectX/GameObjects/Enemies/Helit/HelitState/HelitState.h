#pragma once
#include "../Helit.h"

class Helit;

class HelitState
{
protected:
	Helit* helit;
	float timeAttack;
	float translateY;

public:
	explicit HelitState(Helit *helit);
	virtual ~HelitState() = default;
	virtual ::StateHelit getState() = 0;
	virtual void update(float dt);
		
};
