#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/GamePlayer.h"
#include "../GameObjects/Enemies/Enemies.h"

class DemoScene : public Scene
{

public:
	DemoScene();
	~DemoScene();

	void update(float dt) override;
	void draw() override;

	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

protected:

	void checkCollision(float dt) const;
	void checkCameraAndWorldMap() const;
	void checkCameraAndEnemies() const;

	static void checkCollision(Entity* obj, Entity* other, float dt);
	void checkCollision(Entity* obj, float dt) const;

	GameMap*		pMap;
	Camera*			pCamera;
	GamePlayer*		gp;
	Enemies*		pEnemies;

	std::map<int, bool> keys;

};
#endif