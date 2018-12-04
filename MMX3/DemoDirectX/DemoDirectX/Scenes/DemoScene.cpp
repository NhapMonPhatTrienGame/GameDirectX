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

	pBanger = new Banger();
	pBanger->setPosition(550.0f, 200.0f);

	pGunner = new Gunner();
	pGunner->setPosition(600.0f, 415.0f);

	pHelit = new Helit();
	pHelit->setPosition(900.0f, 300.0f);

	pCarryArms = new CarryArms();
	pCarryArms->setPosition(850.0f, 125.0f);
}

DemoScene::~DemoScene()
{
	delete pMap;
	delete pCamera;
	delete gp;
	delete pBanger;
	delete pGunner;
	delete pHelit;
	delete pCarryArms;
}

void DemoScene::update(float dt)
{
	gp->handlerKeyBoard(keys, dt);

	checkCollision(dt);
	checkCameraAndWorldMap();
	checkCameraAndEnemies();

	pMap->update(dt);
	gp->update(dt);
	pBanger->update(dt);
	pGunner->update(dt);
	pHelit->update(dt);
	pCarryArms->update(dt);
}

void DemoScene::draw()
{
	pMap->draw();
	gp->draw(pCamera);
	pBanger->draw(pCamera);
	pGunner->draw(pCamera);
	pHelit->draw(pCamera);
	pCarryArms->draw(pCamera);
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

void DemoScene::checkCollision(float dt) const
{
	checkCollision(gp, dt);
	checkCollision(pBanger, dt);
	checkCollision(pGunner, dt);
	checkCollision(pHelit, dt);
	checkCollision(pCarryArms, dt);

	pCarryArms->CheckCollision(pMap, dt);

	//gp with pEnemies
	checkCollision(gp, pBanger, dt);
	checkCollision(pBanger, gp, dt);

	checkCollision(gp, pGunner, dt);
	checkCollision(pGunner, gp, dt);

	checkCollision(gp, pHelit, dt);
	checkCollision(pHelit, gp, dt);

	//bulletEnemies checkCollision
	for (auto& Bullet : *pBanger->getBangerBullet())
	{
		//if Bullet Burst don't check Collision
		if (Bullet->getBurst())
			continue;

		checkCollision(Bullet, dt);

		checkCollision(gp, Bullet, dt);
		checkCollision(Bullet, gp, dt);
	}

	//CheckCollision GunnerBullet
	for (auto& bullet : *pGunner->getGunnerBullet())
	{
		if (bullet->getBurst())
			continue;

		checkCollision(bullet, dt);

		checkCollision(gp, bullet, dt);
		checkCollision(bullet, gp, dt);
	}

	for (auto& bullet : *pHelit->getHelitBullet())
	{
		if (bullet->getBurst())
			continue;

		checkCollision(bullet, dt);

		checkCollision(gp, bullet, dt);
		checkCollision(bullet, gp, dt);
	}

	//CheckCollision PlayerBullet
	for (auto& playerBullet : *gp->getPlayerBullet())
	{
		if (playerBullet->getBurst())
			continue;

		checkCollision(pBanger, playerBullet, dt);
		checkCollision(playerBullet, pBanger, dt);

		checkCollision(pGunner, playerBullet, dt);
		checkCollision(playerBullet, pGunner, dt);

		checkCollision(pHelit, playerBullet, dt);
		checkCollision(playerBullet, pHelit, dt);
	}
}

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

void DemoScene::checkCameraAndEnemies()
{
	if (gp->getPosition().x > pBanger->getPosition().x)
		pBanger->setReverse(true);
	else
		pBanger->setReverse(false);

	if (gp->getPosition().x > pGunner->getPosition().x)
		pGunner->setReverse(true);
	else
		pGunner->setReverse(false);

	if (gp->getPosition().x > pHelit->getPosition().x)
		pHelit->setReverse(true);
	else
		pHelit->setReverse(false);

	if (pHelit->getDie())
	{
		if (!GameCollision::isCollision(pCamera->getBound(), pHelit->getBound()))
		{
			pHelit = new Helit();
			pHelit->setPosition(900.0f, 300.0f);
		}
	}

	if (pGunner->getDie())
	{
		if (!GameCollision::isCollision(pCamera->getBound(), pGunner->getBound()))
		{
			pGunner = new Gunner();
			pGunner->setPosition(600.0f, 415.0f);
		}
	}

	if (pBanger->getDie())
	{
		if (!GameCollision::isCollision(pCamera->getBound(), pBanger->getBound()))
		{
			pBanger = new Banger();
			pBanger->setPosition(550.0f, 200.0f);
		}
	}
}

void DemoScene::checkCollision(Entity* obj, float dt) const
{
	std::vector<Entity*> listEntitiesCollision;
	pMap->getQuadTree()->getEntitiesCollideAble(listEntitiesCollision, obj);

	for (auto& i : listEntitiesCollision)
	{
		D3DXVECTOR2 distance = GameCollision::Distance(obj, i, dt);
		RECT broad = GameCollision::getBroad(obj->getBound(), distance);

		if (GameCollision::isCollision(broad, i->getBound()))
		{
			SidesCollision other_with_entity;
			float collision_time = GameCollision::SweptAABB(obj->getBound(), i->getBound(), distance, other_with_entity);

			if (collision_time < 1.0f)
			{
				obj->checkTimeCollision(collision_time, other_with_entity, i);
			}
		}
	}
}

void DemoScene::checkCollision(Entity* obj, Entity* other, float dt)
{
	if (!obj->getDraw() || !other->getDraw() || obj->getDie() || other->getDie())
		return;

	D3DXVECTOR2 distance = GameCollision::Distance(obj, other, dt);
	RECT broad = GameCollision::getBroad(obj->getBound(), distance);

	if (GameCollision::isCollision(broad, other->getBound()))
	{
		SidesCollision pEnemies_with_gp;
		float collision_time = GameCollision::SweptAABB(obj->getBound(), other->getBound(), distance, pEnemies_with_gp);

		if (collision_time < 1.0f)
		{
			obj->onCollision(other);
		}
	}
}