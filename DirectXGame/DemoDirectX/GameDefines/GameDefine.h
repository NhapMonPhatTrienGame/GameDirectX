#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

template<class T>
void SafeDelete(T& pValue)
{
	if(pValue)
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

#define VK_A  0x41;
#define VK_B  0x42;
#define VK_C  0x43;
#define VK_D  0x44;
#define VK_E  0x45;
#define VK_F  0x46;
#define VK_G  0x47;
#define VK_H  0x48;
#define VK_I  0x49;
#define VK_J  0x4A;
#define VK_K  0x4B;
#define VK_L  0x4C;
#define VK_M  0x4D;
#define VK_N  0x4E;
#define VK_P  0x50;
#define VK_Q  0x51;
#define VK_R  0x52;
#define VK_S  0x53;
#define VK_T  0x54;
#define VK_U  0x55;
#define VK_V  0x56;
#define VK_W  0x57;
#define VK_X  0x58;
#define VK_Y  0x59;
#define VK_Z  0x5A;

#define VK_SLIDE 0x43
#define VK_JUMP 0x58
#define VK_SHOOT 0x5A

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
		Win,
		Die
	};
}

namespace Define
{
	const char ANIMATION_STANDING[] = "Resources/mario/standingright.png";
	const char ANIMATION_JUMPING[] = "Resources/mario/jumpingright.png";
	const char ANIMATION_RUNNING[] = "Resources/mario/runningright.png";
	
	const char WORLD_MAP[] = "Resources/marioworld1-1.tmx";

	const float PLAYER_MAX_JUMP_VELOCITY = 480.0f;		//Max jump velocity
	const float PLAYER_MIN_JUMP_VELOCITY = -480.0f;		//Min jump velocity
	const float PLAYER_MAX_RUNNING_SPEED = 350.0f;		//Max speed of layer
	// The collision side with the bottom of the bottom collision is smaller that layer will fall down
	const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f;
	const float PLAYER_MAX_SLIDE_SPEED = 350.0f;
}

#endif
