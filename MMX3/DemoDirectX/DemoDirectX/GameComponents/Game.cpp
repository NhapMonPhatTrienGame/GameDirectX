#include "Game.h"
#include "GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/DemoScene.h"
#include "GameTime.h"
#include <iostream>

Game::Game(int fps)
{
	mFPS = fps;
	SceneManager::getInstance()->ReplaceScene(new DemoScene());
	InitLoop();
}

void Game::Update(float dt)
{
	SceneManager::getInstance()->getCurrentScene()->update(dt);
	Render();
}

void Game::Render()
{
	auto device = GameGlobal::getCurrentDevice();
	auto scene = SceneManager::getInstance()->getCurrentScene();
	device->Clear(0, nullptr, D3DCLEAR_TARGET, scene->getBackColor(), 0.0f, 0);

	{
		device->BeginScene();

		//Starting draw
		GameGlobal::getCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->draw();

		//Ending draw
		GameGlobal::getCurrentSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(nullptr, nullptr, nullptr, nullptr);
}

void Game::InitLoop() const
{
	MSG msg;

	const float tickPerFrame = 1.0f / mFPS;
	float delta = 0;

	while (GameGlobal::isGameRunning)
	{
		GameTime::GetInstance()->StartCounter();

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += GameTime::GetInstance()->GetCounter();

		if (delta >= tickPerFrame)
		{
			Update(delta);
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}
}
