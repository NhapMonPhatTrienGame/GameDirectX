#include "Game.h"
#include <cstdio>
#include "GameTime.h"
#include <string>
#include <iostream>


Game::Game()
{
	_graphics = new Graphics();
	_input = new Input();

	_collision = new Collisions();

	_ballSprite.x = 400;
	_ballSprite.y = 200;
	_ballSprite.width = 25;
	_ballSprite.height = 25;
	_ballSprite._velocityX = 50;
	_ballSprite._velocityY = -50;


	_paddleSprite.x = 0;
	_paddleSprite.y = 300;
	_paddleSprite.width = 17;
	_paddleSprite.height = 175;
	_paddleSprite._velocityY = 150;

	//Thêm 1 cái padd nè 
	_paddleSpriteKey.x = SCREEN_WIDTH - 17;
	_paddleSpriteKey.y = 300;
	_paddleSpriteKey.width = 17;
	_paddleSpriteKey.height = 175;
	_paddleSpriteKey._velocityY = 150;

	Score1 = 0;
	Score2 = 0;
}

Game::~Game()
{
	delete _graphics;
}

bool Game::Game_Init(HWND hWnd)
{
	srand(time_t(NULL));

	//Initialize mouse and keyboard
	if (!_input->CreateInputDevice(hWnd))
	{
		MessageBox(hWnd, "Initialize Input Device Failed", "Error", MB_OK);
		return false;
	}

	//Create sprite handler object
	_result = D3DXCreateSprite(_graphics->getDirect3DDevice(), &_spriteHandler);
	if (FAILED(_result))
		return false;

	//Load the background image
	_back = _graphics->LoadSurFaces("Resources/background.jpg", D3DCOLOR_XRGB(0, 0, 0));
	if (!_back)
		return false;

	//Load the _ballSprite sprite
	_ballImage = _graphics->LoadTexture("Resources/ball.bmp", D3DCOLOR_XRGB(255, 255, 255));
	if (!_ballImage)
		return false;

	// Load the background paddle
	_paddleImage = _graphics->LoadTexture("Resources/paddle_.bmp", D3DCOLOR_XRGB(255, 255, 255));
	return _paddleImage != NULL;
}

void Game::Game_Loop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	float tick_per_frame = 1.0f / FRAME;
	float gameTime = 0;
	int done = 0;

	while(!done)
	{
		GameTime::getInstance()->startCounter();

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		gameTime += GameTime::getInstance()->getCounter();
		if(gameTime >= tick_per_frame)
		{
			Update(gameTime);
			gameTime = 0;
		}
		else
		{
			Sleep(DWORD(tick_per_frame - gameTime));
			gameTime = tick_per_frame;
		}
	}
}

void Game::Render()
{
	//_ballSprite position vector
	D3DXVECTOR3 position(0, 0, 0);

	//make sure your device is valid
	if (!_graphics->getDirect3DDevice()) return;

	//update mouse and keyboard
	_input->ReadMouse();
	_input->ReadKeyboard();

	if (_graphics->getDirect3DDevice()->BeginScene())
	{
		//erase the entire background
		_graphics->getDirect3DDevice()->StretchRect(_back, NULL, _graphics->getBackBuffer(), NULL, D3DTEXF_NONE);

		//start sprite handler
		_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//draw the _ballSprite
		position = D3DXVECTOR3(_ballSprite.x, _ballSprite.y, 0);
		_spriteHandler->Draw(_ballImage, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));

		// Draw the _paddleSprite
		position = D3DXVECTOR3(_paddleSprite.x, _paddleSprite.y, 0);
		_spriteHandler->Draw(_paddleImage, NULL, NULL, &position, D3DCOLOR_XRGB(255, 0, 255));

		// Draw the _paddleSpriteKey
		position = D3DXVECTOR3(_paddleSpriteKey.x, _paddleSpriteKey.y, 0);
		_spriteHandler->Draw(_paddleImage, NULL, NULL, &position, D3DCOLOR_XRGB(255, 0, 255));

		// Draw text


		//stop drawing
		_spriteHandler->End();

		//stop rendering
		_graphics->getDirect3DDevice()->EndScene();
	}

	_graphics->getDirect3DDevice()->Present(NULL, NULL, NULL, NULL);

	//check for mouse button (to exit program)
	if (_input->Mouse_Button(0))
		PostMessage(NULL, WM_DESTROY, 0, 0);

	//check for escape key (to exit program)
	if (_input->Key_Down(DIK_ESCAPE))
		PostMessage(NULL, WM_DESTROY, 0, 0);
}

//---------------------------------------------------------------------------

void Game::Update(float dt)
{
	//Code ở đây nếu nó có va chạm update 2 lần vị trí
	_ballSprite.x += _ballSprite._velocityX * dt;
	_ballSprite.y += _ballSprite._velocityY * dt;


	//check collision after move object
	OnCollision(_ballSprite, _paddleSprite, dt);
	OnCollision(_ballSprite, _paddleSpriteKey, dt);

	//bounce the _ballSprite at screen edges
	//Cái này mày sai nha
	if (_ballSprite.x > SCREEN_WIDTH - _ballSprite.width)
	{
		Score2++;
		//_ballSprite.x -= _ballSprite.width * dt;
		_ballSprite.x = SCREEN_WIDTH - _ballSprite.width;
		_ballSprite._velocityX *= -1;
	}
	else if (_ballSprite.x < 0)
	{
		Score1++;
		//_ballSprite.x += _ballSprite.width * dt;
		_ballSprite.x = 0;
		_ballSprite._velocityX *= -1;
	}

	if (_ballSprite.y > SCREEN_HEIGHT - _ballSprite.height)
	{
		//Score2++;
		//_ballSprite.y -= _ballSprite.height * dt;
		_ballSprite.y = SCREEN_HEIGHT - _ballSprite.height;
		_ballSprite._velocityY *= -1;
	}
	else if (_ballSprite.y < 0)
	{
		//Score1++;
		//_ballSprite.y += _ballSprite.height * dt;
		_ballSprite.y = 0;
		_ballSprite._velocityY *= -1;
	}

	//move the _paddleSprite
	_paddleSpriteKey.y += _input->Mouse_Y();
	

	////check for left arrow
	//if (_input->Key_Down(DIK_LEFT))
	//	_paddleSprite.x -= _paddleSprite._velocityX*dt;

	////check for right arrow
	//if (_input->Key_Down(DIK_RIGHT))
	//	_paddleSprite.x += _paddleSprite._velocityX*dt;

	//check for left arrow
	if (_input->Key_Down(DIK_UP))
		_paddleSprite.y -= _paddleSprite._velocityY * dt;

	//check for right arrow
	if (_input->Key_Down(DIK_DOWN))
		_paddleSprite.y += _paddleSprite._velocityY * dt;

	if (_paddleSprite.y > SCREEN_HEIGHT - _paddleSprite.height)
		_paddleSprite.y = SCREEN_HEIGHT - _paddleSprite.height;
	else if (_paddleSprite.y < 0)
		_paddleSprite.y = 0;

	// Paddle sprite key
	if (_paddleSpriteKey.y > SCREEN_HEIGHT - _paddleSpriteKey.height)
		_paddleSpriteKey.y = SCREEN_HEIGHT - _paddleSpriteKey.height;
	else if (_paddleSpriteKey.y < 0)
		_paddleSpriteKey.y = 0;

	Render();
}

Graphics * Game::getGraphics()
{
	return _graphics;
}

void Game::OnCollision(BOX &box, BOX block, float dt)
{
	BOX broad_phase_box = _collision->GetSweptBroadphaseBox(box);

	if(_collision->isCollision(broad_phase_box, block))
	{
		float normalX, normalY;
		float collision_time = _collision->SweptAABB(box, block, normalX, normalY, dt);

		//Chưa va chạm mà update vị trí nên sai
		//box.x += box._velocityX * collision_time * dt;
		//box.y += box._velocityY * collision_time * dt;

		if (collision_time < 1.0f)
		{
			std::cout << "collision time: " << collision_time << std::endl;
			std::cout << "NormalX: " << normalX << ", NormalY: " << normalY << std::endl;
			//Xử lí time trước khi chạm
			//Khi va chạm rôi mới update collision_time<1
			box.x += box._velocityX * collision_time * dt;
			box.y += box._velocityY * collision_time * dt;
			//---------------------------------------


			//Cái này là time sau khi chậm còn dư
			float remaining_time = 1.0f - collision_time;
			//Chỗ này vì ball có động lực liên tục nên không cần thay đổi vận tốc (Chủ yếu dùng kĩ thuật trượt), 2 dòng code này làm ball nó chậm như shit rơi
			//box._velocityX *= remaining_time;
			//box._velocityY *= remaining_time;

			if (abs(normalX) > 0.0001f)
			{
				//MessageBox(NULL, "normalX", "OK", MB_OK);
				box._velocityX *= -1;

			}
			if (abs(normalY) > 0.0001f)
			{
				//MessageBox(NULL, "normalY", "OK", MB_OK);
				box._velocityY *= -1;
			}
			//quãng đường còn lại
			box.x += box._velocityX * remaining_time * dt;
			box.y += box._velocityY * remaining_time * dt;

			/*float magnitude = sqrt((box._velocityX * box._velocityX + box._velocityY * box._velocityY))*collision_time;
			float dot_prod = box._velocityX * normalX + box._velocityY * normalY;

			if (dot_prod > 0.0f)
				dot_prod = 1.0f;
			else if (dot_prod < 0.0f)
				dot_prod = -1.0f;

			box._velocityX = dot_prod * normalX * magnitude;
			box._velocityY = dot_prod * normalY * magnitude;

			float slide = (box._velocityX * normalX + box._velocityY * normalY) * collision_time;
			box._velocityX = slide * normalY;
			box._velocityY = slide * normalX;*/

		}
	}
}
