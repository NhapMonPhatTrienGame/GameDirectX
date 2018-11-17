#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"

DemoScene::DemoScene()
{
	//Set color for scene. Here is blue scene color 
	mBackColor = 0x54acd2;

	pMap = new GameMap(Define::WORLD_MAP);

	pCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	pCamera->setPosition(GameGlobal::GetWidth() * 0.5f, pMap->getHeight() - pCamera->getHeight());

	pMap->setCamera(pCamera);

	gp = new GamePlayer();

	gp->setPosition(GameGlobal::GetWidth() * 0.5f, 0);
	gp->setCamera(pCamera);

	pEnemies = new Enemies();
	pEnemies->setPosition(GameGlobal::GetWidth() * 0.6, 500);
}

void DemoScene::update(float dt)
{
	gp->handlerKeyBoard(keys, dt);
	CheckCollision(dt);
	pMap->update(dt);
	gp->update(dt);
	pEnemies->update(dt);
	CheckCameraAndWorldMap();
}

void DemoScene::draw()
{
	pMap->draw();
	gp->drawSprite();
	pEnemies->drawSprite();
}

void DemoScene::onKeyDown(int keyCode)
{
	keys[keyCode] = true;
	gp->onKeyDown(keys, keyCode);
}

void DemoScene::onKeyUp(int keyCode)
{
	keys[keyCode] = false;
	gp->onKeyUp(keyCode);
}

void DemoScene::onMouseDown(float x, float y) {}

void DemoScene::CheckCameraAndWorldMap() const
{
	pCamera->setPosition(gp->getPosition());

	if (pCamera->getBound().left < 0)
	{
		//The position of camera is now in the center
		//The position of camera hits the left of the real world
		pCamera->setPosition(pCamera->getWidth() / 2.0f, pCamera->getPosition().y);
		if (gp->getBound().left < 0)
			gp->setPosition(gp->getWidth() / 4.0f, gp->getPosition().y);
	}

	if (pCamera->getBound().right > pMap->getWidth())
	{
		//The position of camera hits the right side of the real world
		pCamera->setPosition(pMap->getWidth() - pCamera->getWidth() / 2.0f, pCamera->getPosition().y);
		if (gp->getBound().right > pMap->getWidth())
			gp->setPosition(pMap->getWidth() - gp->getWidth() / 4.0f, gp->getPosition().y);
	}

	if (pCamera->getBound().top < 0)
	{
		//Now. The position of camera hits the top of the real world
		pCamera->setPosition(pCamera->getPosition().x, pCamera->getHeight() / 2.0f);
		if (gp->getBound().top < 0)
			gp->setPosition(gp->getPosition().x, gp->getHeight() / 4.0f);
	}

	if (pCamera->getBound().bottom > pMap->getHeight())
	{
		//Now. the position of camera hits the bottom of the real world
		pCamera->setPosition(pCamera->getPosition().x, pMap->getHeight() - pCamera->getHeight() / 2.0f);
		if (gp->getBound().bottom > pMap->getHeight())
		{
			//Layer has a die state
			gp->setState(new DieState(gp));
		}
	}
}

DemoScene::~DemoScene()
{
	SAFE_DELETE(pMap);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(gp);
	SAFE_DELETE(pEnemies);
}

void DemoScene::CheckCollision(float dt) const
{
	/*Used to check when mario does not stand on an object or stand over the left or right edge of the object that will translate FallingState.*/
	bool isBottom = false;

	std::vector<Entity*> listEntitiesCollision;

	pMap->getQuadTree()->getEntitiesCollideAble(listEntitiesCollision, gp);

	for (auto& i : listEntitiesCollision)
	{
		const auto distance = GameCollision::Distance(gp, i, dt);
		const auto broad = GameCollision::GetBoard(gp->getBound(), distance);

		if (GameCollision::isCollide(broad, i->getBound()))
		{
			Entity::SideCollisions entityWithPlayer;
			const auto collisionTime = GameCollision::SweptAABB(gp->getBound(), i->getBound(), distance, entityWithPlayer);

			if (collisionTime < 1.0f)
			{
				gp->updateCollision(collisionTime, entityWithPlayer, dt);
				gp->onCollision(entityWithPlayer);
				if (entityWithPlayer == Entity::Bottom)
					isBottom = true;
			}
		}
	}

	if (!isBottom)
		gp->onNoCollisionWithBottom();


#pragma region Enemies
	bool isEnemiesBottom = false;
	std::vector<Entity *> listEntityCollide;
	pMap->getQuadTree()->getEntitiesCollideAble(listEntityCollide, pEnemies);

	for (auto& i : listEntityCollide)
	{
		const auto distance = GameCollision::Distance(pEnemies, i, dt);
		const auto broad = GameCollision::GetBoard(pEnemies->getBound(), distance);

		if (GameCollision::isCollide(broad, i->getBound()))
		{
			Entity::SideCollisions entitiesWithEnemies;
			const auto collisionTime = GameCollision::SweptAABB(pEnemies->getBound(), i->getBound(), distance, entitiesWithEnemies);

			if (collisionTime < 1.0f)
			{
				pEnemies->updateCollision(collisionTime, entitiesWithEnemies, dt);
				pEnemies->onCollision(entitiesWithEnemies);
				if (entitiesWithEnemies == Entity::Bottom)
					isEnemiesBottom = true;
			}
		}
	}

	if (!isEnemiesBottom)
		pEnemies->onCollisionBottom();
#pragma endregion 
}
