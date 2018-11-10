#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "../GameComponents/Scene.h"

class SceneManager
{
	static SceneManager     *mInstance;
	Scene                   *mCurrentScene;

public:
    static SceneManager *GetInstance();

	SceneManager();
    ~SceneManager() = default;

    Scene* GetCurrentScene() const;
    void Update(float dt) const;
    void ReplaceScene(Scene *scene);
};

#endif