#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__
#include "../Entity/Entity.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/Animation.h"
#include <map>
#include "PlayerBullet/PlayerBullet.h"

class GameState;

enum class PlayerState
{
	Appear,
	Stand,
	Run,
	Fall,
	Jump,
	Cling,
	Climb,
	SlipDown,
	Dash,
	Bleed,
	Win,
	Die
};

enum class Move
{
	MoveLeft,
	MoveRight,
	None
};

class GamePlayer : public Entity
{
protected:

	GameState*			pState;
	Animation*			pAnimation;

	float				timeShoot;
	float				timeCurrentShoot;
	float				timeChangeShoot;
	float				timeAlive;

	bool				isShoot;
	bool				allowJump;
	bool				allowShoot;
	bool				allowDash;
	bool				alive;

	float				HP;
	PlayerState			currentState;

	std::vector<PlayerBullet*> listBullet;

public:

	GamePlayer();
	~GamePlayer();

	void changeAnimation(PlayerState state);

	void setState(GameState* newState);

	PlayerState getState() const							{ return currentState; }
	Animation* getAnimation() const							{ return pAnimation; }

	float getHP() const										{ return HP; }
	void setHP(float hp)									{ HP = hp; }
	void addHP(float hp)									{ HP += hp; }

	std::vector<PlayerBullet*> *getPlayerBullet()			{ return &listBullet; }

	Move getMoveDirection() const;

	void handlerKeyBoard(const map<int, bool>& keys, float dt) const;
	void onKeyDown(std::map<int, bool> keys, int Key);
	void onKeyUp(int Key);

	RECT getBound() override;

	void update(float dt) override;
	void draw(Camera *camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0.0f, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

	void onCollision(SidesCollision side) override;
	void onNoCollisionWithBottom() override;
	void onCollision(Entity* enemies) override;

	void PlayerShoot(BulletType bulletType);
};

#endif