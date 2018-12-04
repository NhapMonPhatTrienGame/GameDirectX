#ifndef HELIT_H
#define HELIT_H

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "HelitBullet/HelitBullet.h"

class HelitState;
class Camera;

enum class StateHelit
{
	Stand,
	Attack,
	Die,
	None
};

class Helit :
	public Entity
{
protected:

	Animation*					anim;
	Animation*					animDie;
	HelitState*					pState;
	StateHelit					currentState;
	int							HP;
	std::vector<HelitBullet*>   listBullet;

public:

	Helit();
	~Helit();

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(Entity* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = NULL);

	void setState(HelitState *newState);
	void changeAnimation(StateHelit state);

	std::vector<HelitBullet*> *getHelitBullet() { return &listBullet; }
};

#endif