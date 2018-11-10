#pragma once

#include "../GameComponents/Scene.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/GamePlayer.h"

class DemoScene : public Scene
{
protected:
	void CheckCollision() const;
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
