#ifndef _GAME_H
#define _GAME_H

#include "dxgraphics.h"
#include "dxinput.h"
#include <Windows.h>
#include <d3d9.h>
#include "Collisions.h"

#define APP_TITLE "PingPong"

#define WINDOW_POS_X 1630
#define WINDOW_POS_Y 85

#define FULL_SCREEN 0
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700

#define FRAME 30




class Game {

	Collisions* _collision;

	LPDIRECT3DSURFACE9 _back;

	//sprite handler
	LPD3DXSPRITE _spriteHandler;

	//_ballSprite sprite
	LPDIRECT3DTEXTURE9 _ballImage;
	BOX _ballSprite;

	//_paddleSprite sprite
	LPDIRECT3DTEXTURE9 _paddleImage;
	BOX _paddleSprite;
	BOX _paddleSpriteKey;

	HRESULT _result;

	Graphics* _graphics;

	Input* _input;

	int Score1;
	int Score2;

public:
	Game();
	~Game();

	bool Game_Init(HWND hWnd);

	void Game_Loop();

	void Render();

	void Update(float dt);

	Graphics* getGraphics();

	void OnCollision(BOX &box, BOX block, float dt);

};
#endif