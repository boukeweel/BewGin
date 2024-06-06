#include "SceneManager.h"

#include <iostream>

#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "../Galiga/GameEntityData.h"

void bew::SceneManager::FixedUpdate()
{
	m_scenes[m_CurrentScene]->FixedUpdate();
}

void bew::SceneManager::Update()
{
	m_scenes[m_CurrentScene]->Update();
}

void bew::SceneManager::Render() const
{
	m_scenes[m_CurrentScene]->Render();
}

bew::Scene& bew::SceneManager::CreateScene(const std::string& name, std::unique_ptr<BaseSceneCreator> load)
{
	//checking if a other scene with the same name exists
	for (const auto& scene : m_scenes)
	{
		if (scene->GetName().size() == name.size())
		{
			if (scene->GetName() == name)
			{
				std::cout << "You where trying to create a scene with the name: " << name << " but a differenct scene with the same name already exists\n";
				return *m_scenes[scene->GetId()];
			}
		}
	}

	const auto& scene = std::shared_ptr<Scene>(new Scene(name,std::move(load)));
	m_scenes.push_back(scene);
	return *scene;
}

void bew::SceneManager::LoadScene(unsigned int idScene)
{
	m_scenes[m_CurrentScene]->RemoveAll();
	GameEntityData::GetInstance().ResetAll();
	m_Objects.clear();
	m_CurrentScene = idScene;
	m_scenes[m_CurrentScene]->LoadInScene();
}

void bew::SceneManager::AddToCurrentScene(std::unique_ptr<GameObject> obj)
{
	m_Objects.emplace_back(std::move(obj));
}

void bew::SceneManager::LoadingInNewObjects()
{
	for (auto& obj : m_Objects) {
		GetCurrentScene().Add(std::move(obj));
	}
	m_Objects.clear();
}

