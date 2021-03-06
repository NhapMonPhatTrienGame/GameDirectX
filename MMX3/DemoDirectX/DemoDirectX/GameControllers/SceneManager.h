#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "../GameComponents/Scene.h"

class SceneManager
{
private:
	static SceneManager*	 m_Instance;
	Scene*					 m_CurrentScene;

public:
	static SceneManager* getInstance();

	SceneManager();
	~SceneManager();

	Scene* getCurrentScene() const;
	void Update(float dt) const;
	void ReplaceScene(Scene* scene);

};

#endif
