#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"

DemoScene::DemoScene()
{
	DemoScene::LoadContent();
}

void DemoScene::LoadContent()
{
	//Set color for scene. Here is blue scene color 
	mBackColor = 0x54acd2;

	pMap = new GameMap(Define::WORLD_MAP);

	pCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	pCamera->SetPosition(GameGlobal::GetWidth() / 2.0f,
		pMap->GetHeight() - pCamera->GetHeight());

	pMap->SetCamera(pCamera);

	gp = new GamePlayer();

	gp->setPosition(GameGlobal::GetWidth() / 2.0f, 0);
	gp->SetCamera(pCamera);
}

void DemoScene::Update(float dt)
{
	gp->HandleKeyboard(keys, dt);
	CheckCollision(dt);
	pMap->Update(dt);
	gp->Update(dt);

	CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
	pMap->Draw();
	gp->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	gp->OnKeyDown(keys, keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	gp->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y) {}

void DemoScene::CheckCameraAndWorldMap() const
{
	pCamera->SetPosition(gp->getPosition());

	if (pCamera->GetBound().left < 0)
	{
		//The position of camera is now in the center
		//The position of camera hits the left of the real world
		pCamera->SetPosition(pCamera->GetWidth() / 2.0f, pCamera->GetPosition().y);
		if (gp->getBound().left < 0)
			gp->setPosition(gp->getWidth() / 4.0f, gp->getPosition().y);
	}

	if (pCamera->GetBound().right > pMap->GetWidth())
	{
		//The position of camera hits the right side of the real world
		pCamera->SetPosition(pMap->GetWidth() - pCamera->GetWidth() / 2.0f, pCamera->GetPosition().y);
		if (gp->getBound().right > pMap->GetWidth())
			gp->setPosition(pMap->GetWidth() - gp->getWidth() / 4.0f, gp->getPosition().y);
	}

	if (pCamera->GetBound().top < 0)
	{
		//Now. The position of camera hits the top of the real world
		pCamera->SetPosition(pCamera->GetPosition().x, pCamera->GetHeight() / 2.0f);
		if (gp->getBound().top < 0)
			gp->setPosition(gp->getPosition().x, gp->getHeight() / 4.0f);
	}

	if (pCamera->GetBound().bottom > pMap->GetHeight())
	{
		//Now. the position of camera hits the bottom of the real world
		pCamera->SetPosition(pCamera->GetPosition().x, pMap->GetHeight() - pCamera->GetHeight() / 2.0f);
		if (gp->getBound().bottom > pMap->GetHeight())
		{
			//Layer has a die state
			gp->setState(new DieState(gp));
		}
	}
}

void DemoScene::CheckCollision(float dt) const
{
	/*Used to check when mario does not stand on an object or stand over the left or right edge of the object that will translate FallingState.*/
	bool isBottom = false;

	std::vector<Entity*> listEntitiesCollision;

	pMap->GetQuadTree()->getEntitiesCollideAble(listEntitiesCollision, gp);

	for (auto& i : listEntitiesCollision)
	{
		D3DXVECTOR2 distance = GameCollision::Distance(gp, i, dt);
		RECT broad = GameCollision::GetBoard(gp->getBound(), distance);

		if (GameCollision::isCollide(broad, i->getBound()))
		{
			Entity::SideCollisions entityWithPlayer;
			float collisionTime = GameCollision::SweptAABB(gp->getBound(), i->getBound(), distance, entityWithPlayer);

			if (collisionTime < 1.0f)
			{
				gp->UpdateColision(collisionTime, entityWithPlayer, dt);
				gp->OnCollision(entityWithPlayer);
				if (entityWithPlayer == Entity::Bottom)
					isBottom = true;
			}
		}
	}

	if (!isBottom)
		gp->OnNoCollisionWithBottom();
}
