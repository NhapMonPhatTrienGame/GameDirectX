#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/GamePlayer.h"
#include "../Enemies.h"

class DemoScene : public Scene
{
protected:

	void CheckCollision(float dt) const;
	void CheckCameraAndWorldMap() const;

	GameMap*		pMap;
	Camera*			pCamera;
	GamePlayer*		gp;
	Enemies*		pEnemies;

	std::map<int, bool> keys;

public:
	DemoScene();
	~DemoScene();

	void update(float dt) override;
	void draw() override;

	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;
	void onMouseDown(float x, float y) override;	
};
#endif
