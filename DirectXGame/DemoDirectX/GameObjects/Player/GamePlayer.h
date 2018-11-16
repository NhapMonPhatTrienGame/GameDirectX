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
	bool				m_CurrentReverse;
	StateName			m_CurrentState;
	float				m_TimeShoot;
	float				m_TimeCurrentShoot;
	bool				m_Shoot;
	bool				m_AllowJump;
	bool				m_AllowShoot;
	bool				m_AllowSlide;
	float				m_HP;

public:

	GamePlayer();
	~GamePlayer();

	enum MoveDirection
	{
		MoveToLeft,		// Move left
		MoveToRight,	// Move right
		None			// Stand
	};

	void ChangeAnimation(StateName state);

	void setState(GameState* newState);

	StateName getState() const			{ return m_CurrentState; }
	Animation* getAnimation() const		{ return pAnimation; }
	void setCamera(Camera* camera)		{ pCamera = camera; }

	float getHP() const					{ return m_HP; }
	void setHP(float hp)				{ m_HP = hp; }
	void addHP(float hp)				{ m_HP += hp; }

	MoveDirection getMoveDirection() const;

	void HandleKeyboard(const map<int, bool>& keys, float dt) const;
	void OnKeyDown(std::map<int, bool> keys, int Key);
	void OnKeyUp(int Key);

	void setReverse(bool flag)			{ m_CurrentReverse = flag; }
	bool getReverse() const				{ return m_CurrentReverse; }

	RECT getBound() override;

	void Update(float dt) override;
	void Draw(D3DXVECTOR3 Position = D3DXVECTOR3(), RECT SourceRect = RECT(), 
		D3DXVECTOR2 Scale = D3DXVECTOR2(),
		D3DXVECTOR2 Translate = D3DXVECTOR2(), float Angle = 0, D3DXVECTOR2 RotationCenter = D3DXVECTOR2(),
		D3DXCOLOR TransColor = D3DCOLOR_XRGB(255, 255, 255));

	void OnCollision(SideCollisions side) override;
	void OnNoCollisionWithBottom();
};
