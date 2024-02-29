#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject() = default;




void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& element : m_pComponents)
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

std::shared_ptr<dae::GameObject> dae::GameObject::GetParrent()
{
	return m_pParent;
}

void dae::GameObject::SetParrent(std::shared_ptr<GameObject> pParent)
{

}

int dae::GameObject::GetChildCount()
{
	return static_cast<int>(m_pChildren.size());
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAtIndex(int index)
{
	return m_pChildren[index];
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{

}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{

}

