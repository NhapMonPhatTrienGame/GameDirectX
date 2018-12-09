#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__


// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

#define VK_SLIDE	0x43
#define VK_JUMP		0x58
#define VK_SHOOT	0x5A

namespace Define
{
	const char ANIMATION_ROCKMAN[] = "Resources/rockman/Rockman_49x49_backfround(100,100,100).png";
	const char PLAYER_BULLET[] = "Resources/rockman/RockManBullet.png";
	const char EFFECTS_BULLET[] = "Resources/rockman/RockMan.png";

	const char NOTOR_BANGER_BULLET[] = "Resources/Enemies/NotorBanger/NotorBangerBullet.png";
	const char NOTOR_BANGER_SPRITE[] = "Resources/Enemies/NotorBanger/NotorBangerSprite.png";

	const char HEAD_GUNNER_SPRITE[] = "Resources/Enemies/HeadGunnerCustomer/HeadGunnerSpriteSheet.png";
	const char HEAD_GUNNER_BULLET[] = "Resources/Enemies/HeadGunnerCustomer/HeadGunnerBullet.png";

	const char GUNNER_DIE[] = "Resources/Enemies/HeadGunnerCustomer/GunnerDie.png";
	const char BANGER_DIE[] = "Resources/Enemies/NotorBanger/NotorBangerDie.png";

	const char HELIT_SPRITE_SHEET[] = "Resources/Enemies/Helit/HelitSpriteSheet.png";
	const char HELIT_BULLET[] = "Resources/Enemies/Helit/HelitBullet.png";
	const char HELIT_DIE[] = "Resources/Enemies/Helit/HelitDie.png";

	const char CARRY_ARM[] = "Resources/Enemies/CarryArm/CarryArmsSpriteSheet.png";

	const char BOX[] = "Resources/Box_36x36.png";

	const char BURST[] = "Resources/Enemies/Boom.png";

	//const char WORLD_MAP[] = "Resources/marioworld1-1.tmx";
	const char WORLD_MAP[] = "Resources/MapTestSubBoss.tmx";

	const float PLAYER_MAX_JUMP_VELOCITY = 300.0f; //Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -300.0f; //Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 150.0f; //Max speed of layer
	const float PLAYER_MAX_CLING_SPEED = 30.0f; //Max speed of layer
	const float PLAYER_MAX_SLIDE_SPEED = 300.0f;

	const float ENEMY_MAX_JUMP_VELOCITY = 300.0f;
	const float ENEMY_MIN_JUMP_VELOCITY = -300.0f;
}

#endif