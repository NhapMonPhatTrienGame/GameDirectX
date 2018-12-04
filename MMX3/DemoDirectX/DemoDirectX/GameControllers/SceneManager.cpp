#include "SceneManager.h"

SceneManager* SceneManager::m_Instance = nullptr;

SceneManager::SceneManager()
{
	m_CurrentScene = nullptr;
}

SceneManager::~SceneManager()
{
	if(m_Instance)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

SceneManager* SceneManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new SceneManager();

	return m_Instance;
}

Scene* SceneManager::getCurrentScene() const
{
	return m_CurrentScene;
}

void SceneManager::Update(float dt) const
{
	m_CurrentScene->update(dt);
}

void SceneManager::ReplaceScene(Scene* scene)
{
	delete m_CurrentScene;
	m_CurrentScene = scene;
}
