#include "GameEffect.h"
#include <iostream>
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameObjects\Entity\Entity.h"
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameObjects\Player\GamePlayer.h"
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameDefines\GameDefine.h"
#include "C:\Users\DELL\GameDirectX\MMX3\DemoDirectX\DemoDirectX\GameComponents\GameGlobal.h"


GameEffect::GameEffect()
{
	tag = Tag::RockMan;
	pAnimation = new Animation(Define::EFFECTS_BULLET, 21, 10, 49, 49, 0.15, D3DCOLOR_XRGB(100, 100, 100));

	
}


GameEffect::~GameEffect()
{
	delete pAnimation;
}
