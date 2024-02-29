#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject() = default;



void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& element : m_Components)
	{
		element->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}

