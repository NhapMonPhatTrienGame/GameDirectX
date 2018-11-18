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

	pCamera = new Camera(GameGlobal::getWidth(), GameGlobal::getHeight());
	pCamera->setPosition(GameGlobal::getWidth() / 2.0f, pMap->getHeight() - pCamera->getHeight());

	pMap->setCamera(pCamera);

	gp = new GamePlayer();
	gp->setPosition(700.0f, 250.0f);

	pEnemies = new Enemies();
	pEnemies->setPosition(550, 200.0f);
}

void DemoScene::update(float dt)
{
	gp->handlerKeyBoard(keys, dt);

	checkCollision(dt);

	pMap->update(dt);
	gp->update(dt);
	pEnemies->update(dt);

	if (gp->getPosition().x > pEnemies->getPosition().x)
		pEnemies->setFlip(true);
	else
		pEnemies->setFlip(false);

	checkCameraAndWorldMap();
	checkCameraAndEnemies();
}

void DemoScene::draw()
{
	pMap->draw();
	gp->drawSprite(pCamera);
	pEnemies->drawSprite(pCamera);
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

void DemoScene::checkCameraAndWorldMap() const
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

void DemoScene::checkCameraAndEnemies() const
{
	if (GameCollision::isCollision(pCamera->getBound(), pEnemies->getBound()))
		pEnemies->setDrawSprite(true);
	else
		pEnemies->setDrawSprite(false);
}

DemoScene::~DemoScene()
{
	SAFE_DELETE(pMap);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(gp);
	SAFE_DELETE(pEnemies);
}
void DemoScene::checkCollision(float dt) const
{
	checkCollision(gp, dt);
	checkCollision(pEnemies, dt);

	//gp with pEnemies
	D3DXVECTOR2 distance = GameCollision::Distance(gp, pEnemies, dt);
	RECT broad = GameCollision::GetBoard(gp->getBound(), distance);

	if (GameCollision::isCollide(broad, pEnemies->getBound()))
	{
		Entity::SideCollisions pEnemies_with_gp;
		float collision_time = GameCollision::SweptAABB(gp->getBound(), pEnemies->getBound(), distance, pEnemies_with_gp);

		if (collision_time < 1.0f)
		{
			gp->onCollision(pEnemies);
		}
	}
}

void DemoScene::checkCollision(Entity *obj, float dt) const
{
	std::vector<Entity*> listEntitiesCollision;

	pMap->getQuadTree()->getEntitiesCollideAble(listEntitiesCollision, obj);

	for (auto& i : listEntitiesCollision)
	{
		D3DXVECTOR2 distance = GameCollision::Distance(obj, i, dt);
		RECT broad = GameCollision::GetBoard(obj->getBound(), distance);

		if (GameCollision::isCollide(broad, i->getBound()))
		{
			Entity::SideCollisions other_with_entity;
			float collision_time = GameCollision::SweptAABB(obj->getBound(), i->getBound(), distance, other_with_entity);

			if (collision_time < 1.0f)
			{
				obj->checkTimeCollision(collision_time, other_with_entity, i);
			}
		}
	}
}