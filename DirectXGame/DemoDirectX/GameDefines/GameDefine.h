#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

template<class T>
void SafeDelete(T& pValue)
{
	if (pValue)
	{
		delete pValue;
		pValue = nullptr;
	}
}

template<class T>
void SafeRelease(T& pValue)
{
	if (pValue)
	{
		pValue->Release();
		pValue = nullptr;
	}
}

#define SAFE_DELETE(p) SafeDelete(p)
#define SAFE_RELEASE(p) SafeRelease(p)

constexpr auto VK_A = 0x41;
constexpr auto VK_B = 0x42;
constexpr auto VK_C = 0x43;
constexpr auto VK_D = 0x44;
constexpr auto VK_E = 0x45;
constexpr auto VK_F = 0x46;
constexpr auto VK_G = 0x47;
constexpr auto VK_H = 0x48;
constexpr auto VK_I = 0x49;
constexpr auto VK_J = 0x4A;
constexpr auto VK_K = 0x4B;
constexpr auto VK_L = 0x4C;
constexpr auto VK_M = 0x4D;
constexpr auto VK_N = 0x4E;
constexpr auto VK_P = 0x50;
constexpr auto VK_Q = 0x51;
constexpr auto VK_R = 0x52;
constexpr auto VK_S = 0x53;
constexpr auto VK_T = 0x54;
constexpr auto VK_U = 0x55;
constexpr auto VK_V = 0x56;
constexpr auto VK_W = 0x57;
constexpr auto VK_X = 0x58;
constexpr auto VK_Y = 0x59;
constexpr auto VK_Z = 0x5A;

constexpr auto VK_SLIDE = 0x43;
constexpr auto VK_JUMP  = 0x58;
constexpr auto VK_SHOOT = 0x5A;

namespace MegaManState
{
	enum StateName
	{
		Appear,
		Standing,
		Running,
		Falling,
		Jumping,
		Cling,
		Climb,
		SlideVertical,
		SlideHorizontal,
		Bleed,
		Win,
		Die
	};
}

namespace Define
{
	const char ANIMATION_ROCKMAN[] = "Resources/mario/Rockman_49x49_backfround(100,100,100).png";
	const char INTRO_ENEMIES[] = "Resources/Intro_Enemies.png";
	const char WORLD_MAP[] = "Resources/marioworld1-1.tmx";

	const float PLAYER_MAX_JUMP_VELOCITY = 300.0f;		//Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -300.0f;		//Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 150.0f;		//Max speed of layer
	const float PLAYER_MAX_CLIING_SPEED = 50.0f;		//Max speed of layer
	const float PLAYER_MAX_SLIDE_SPEED = 300.0f;
}

#endif
