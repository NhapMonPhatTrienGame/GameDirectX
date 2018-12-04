#include "Scene.h"

Scene::Scene()
{
	mBackColor = 0x4866ff;
}

void Scene::update(float dt) {}

void Scene::draw() {}

void Scene::onKeyDown(int keyCode) {}

void Scene::onKeyUp(int keyCode) {}

void Scene::onMouseDown(float x, float y) {}

D3DCOLOR Scene::getBackColor() const
{
	return mBackColor;
}
