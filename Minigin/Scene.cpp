#include "Scene.h"
#include "GameObject.h"

#include <algorithm>
#include <iostream>

#include "InputManager.h"

using namespace bew;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name, std::unique_ptr<BaseSceneCreator> load) : m_name(name), m_id(m_idCounter++), m_pLoad{ std::move(load) } {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
	bew::InputManager::GetInstance().RemoveAllCommands();
}

void Scene::LoadInScene()
{
	m_pLoad->Load();
}

void Scene::ChangeActiveStateInScene(bool state)
{
	for (auto& object : m_pObjects)
	{
		object->SetIsActive(state);
	}
}

void bew::Scene::FixedUpdate()
{
	for (auto& object : m_pObjects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for(auto& object : m_pObjects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

