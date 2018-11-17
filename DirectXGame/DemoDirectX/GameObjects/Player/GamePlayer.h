#pragma once


#include "../Entity/Entity.h"
#include "../../GameComponents/Camera.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/Animation.h"
#include <map>

using namespace MegaManState;

class GameState;

class GamePlayer : public Entity
{
protected:

	GameState*			pState;
	Camera*				pCamera;
	Animation*			pAnimation;
	bool				currentReverse;
	StateName			currentState;
	float				timeShoot;
	float				timeCurrentShoot;
	bool				isShoot;
	bool				allowJump;
	bool				allowShoot;
	bool				allowDash;
	float				HP;

public:

	GamePlayer();
	~GamePlayer();

	enum MoveDirection
	{
		MoveToLeft,		// Move left
		MoveToRight,	// Move right
		None			// Stand
	};

	void changeAnimation(StateName state);

	void setState(GameState* newState);

	StateName getState() const			{ return currentState; }
	Animation* getAnimation() const		{ return pAnimation; }
	void setCamera(Camera* camera)		{ pCamera = camera; }

	float getHP() const					{ return HP; }
	void setHP(float hp)				{ HP = hp; }
	void addHP(float hp)				{ HP += hp; }

	MoveDirection getMoveDirection() const;

	void handlerKeyBoard(const map<int, bool>& keys, float dt) const;
	void onKeyDown(std::map<int, bool> keys, int Key);
	void onKeyUp(int Key);

	void setReverse(bool flag)			{ currentReverse = flag; }
	bool getReverse() const				{ return currentReverse; }

	RECT getBound() override;

	void update(float dt) override;
	void drawSprite(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(), 
		D3DXVECTOR2 Scale = D3DXVECTOR2(),
		D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0, D3DXVECTOR2 RotationCenter = D3DXVECTOR2(),
		D3DXCOLOR TransColor = D3DCOLOR_XRGB(255, 255, 255));

	void onCollision(SideCollisions side) override;
	void onNoCollisionWithBottom();
};
