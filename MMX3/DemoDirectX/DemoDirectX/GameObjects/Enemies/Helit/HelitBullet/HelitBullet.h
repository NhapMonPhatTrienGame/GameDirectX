#ifndef HELIT_BULLET_H
#define HELIT_BULLET_H
#include "../../Gunner/GunnerBullet/GunnerBullet.h"

class HelitBullet :public GunnerBullet
{
protected:
	void changeState(BulletState state) override;

private:
	BulletState bulletState;
	Animation* animBurst;

public:
	HelitBullet();
	~HelitBullet();

	void newBullet(float bx, float by, bool direction) override;
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(SidesCollision side) override;
	void onCollision(Entity* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

};

#endif
