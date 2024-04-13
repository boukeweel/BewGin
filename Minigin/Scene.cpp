#include "Scene.h"
#include "GameObject.h"

#include <algorithm>
#include <iostream>

#include "InputManager.h"

using namespace bew;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name, std::unique_ptr<BaseSceneCreator> load) : m_name(name), m_id(m_idCounter++), m_Load{ std::move(load) } {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
	bew::InputManager::GetInstance().RemoveAllCommands();
}

void Scene::LoadInScene()
{
	m_Load->Load();
}

void Scene::ChangeActiveStateInScene(bool state)
{
	for (auto& object : m_objects)
	{
		object->SetIsActive(state);
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

