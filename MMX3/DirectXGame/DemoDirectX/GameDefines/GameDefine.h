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
	const char ENEMIES_BULLET[] = "Resources/Enemies/bullet_burst.png";
	const char ENEMIES_SPRITE_SHEET[] = "Resources/Enemies/EnemiesSprite.png";

	const char INTRO_ENEMIES[] = "Resources/Enemies/EnemiesSpriteSheet.png";
	const char ENEMIES_STAND[] = "Resources/Enemies/EnemiesStand.png";
	const char ENEMIES_JUMP[] = "Resources/Enemies/EnemiesJump.png";
	const char ENEMIES_GUN[] = "Resources/Enemies/EnemiesGun.png";

	const char WORLD_MAP[] = "Resources/marioworld1-1.tmx";

	const float PLAYER_MAX_JUMP_VELOCITY = 300.0f; //Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -300.0f; //Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 150.0f; //Max speed of layer
	const float PLAYER_MAX_CLING_SPEED = 30.0f; //Max speed of layer
	const float PLAYER_MAX_SLIDE_SPEED = 300.0f;

	const float ENEMY_MAX_JUMP_VELOCITY = 300.0f;
	const float ENEMY_MIN_JUMP_VELOCITY = -300.0f;
}

#endif
