#ifndef __GAME_EFFECT_H__
#define __GAME_EFFECT_H__
#include <map>
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameObjects\Entity\Entity.h"
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameObjects\Player\GamePlayer.h"
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameComponents\Animation.h"
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameComponents\Camera.h"

enum class PlayerState
{
	Effect,
	Effect2
};


class GameEffect : public Entity
{
protected:
	Animation*			pAnimation;

public:
	GameEffect();
	~GameEffect();
};
#endif
