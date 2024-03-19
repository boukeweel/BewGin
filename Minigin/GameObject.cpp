#include "GameObject.h"

#include <iostream>

#include "ResourceManager.h"

dae::GameObject::GameObject() : m_PositionDirty{ false }
{
}

void dae::GameObject::Update()
{
	for (auto& component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto& element : m_pComponents)
	{
		element->Render();
	}
}

dae::Transform dae::GameObject::GetTransform() const
{

	return m_transform;
}

void dae::GameObject::Translate(const glm::vec3& translation)
{
	SetLocalPosition(m_LocalPosition + translation);
}

#pragma region hierargie
dae::GameObject* dae::GameObject::GetParrent() const
{
	return m_pParent;
}

void dae::GameObject::SetParrent(GameObject* pParent, bool KeepWorldPosition)
{
	if (m_pParent == pParent || pParent == this || IsChild(pParent))
	{
		return;
	}

	if (pParent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (KeepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition() - m_pParent->GetWorldPosition());
		}
		SetPositionDirty();
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = pParent;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

dae::GameObject* dae::GameObject::GetChildAtIndex(int index) const
{
	return m_pChildren[index];
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	child->SetParrent(nullptr);
}

bool dae::GameObject::IsChild(GameObject* newParent) const
{
	auto it = std::find(std::begin(m_pChildren), std::end(m_pChildren), newParent);

	return it != std::end(m_pChildren);
}
#pragma endregion

#pragma region Postion
void dae::GameObject::SetPosition(float x, float y)
{
	SetLocalPosition({ x,y,0 });

	m_transform.SetPosition(GetWorldPosition());
}

void dae::GameObject::SetPosition(const glm::vec3& pos)
{
	SetPosition(pos.x, pos.y);
}

glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionDirty = true;

	if (!m_pChildren.empty())
	{
		for (const auto child : m_pChildren)
		{
			child->SetPositionDirty();
		}
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionDirty)
	{
		if (m_pParent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
		}
	}
}

#pragma endregion


