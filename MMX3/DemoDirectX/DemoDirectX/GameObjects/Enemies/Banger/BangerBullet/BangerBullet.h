#pragma once
#include "../../../Entity/Entity.h"
#include "../../Gunner/GunnerBullet/GunnerBullet.h"

class Camera;

class BangerBullet :
	public GunnerBullet
{
protected:
	void changeState(BulletState state) override;

private:
	float				bulletY;	// The bullet translate to y axis

public:
	BangerBullet();
	~BangerBullet();

	RECT getBound() override;
	void newBullet(float bx, float by, bool direction) override;
	void update(float dt) override;
	void onCollision(SidesCollision side) override;
	void onCollision(Entity* obj) override;

};