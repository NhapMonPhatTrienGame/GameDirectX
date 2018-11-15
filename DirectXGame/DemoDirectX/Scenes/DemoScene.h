#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/GamePlayer.h"

class DemoScene : public Scene
{
protected:
	void CheckCollision(float dt) const;
	void CheckCameraAndWorldMap() const;

	GameMap		*pMap;
	Camera		*pCamera;

	GamePlayer	*gp;

	std::map<int, bool> keys;

public:
	DemoScene();
	~DemoScene() = default;

	void Update(float dt) override;
	void LoadContent() override;
	void Draw() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnMouseDown(float x, float y) override;
};
#endif
