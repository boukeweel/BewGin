#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

bew::GameObject::GameObject() : m_PositionDirty{ false }
{
}



//bew::GameObject::GameObject(const bew::GameObject& other) :
//	m_transform(other.m_transform),
//	m_WorldPosition(other.m_WorldPosition),
//	m_LocalPosition(other.m_LocalPosition),
//	m_pParent(nullptr), // The copied object will initially have no parent
//	m_IsActive(other.m_IsActive)
//{
//	// Copy components
//	m_pComponents.reserve(other.m_pComponents.size());
//	for (const auto& component : other.m_pComponents)
//	{
//		
//		//m_pComponents.push_back(component->Clone(this)); // Assuming Clone function exists in Component class
//	}
//
//
//	auto& scene = SceneManager::GetInstance().GetCurrentScene();
//
//	//copy the children
//	m_pChildren.reserve(other.m_pChildren.size());
//	for (const auto& child : other.m_pChildren)
//	{
//		auto newChild = std::make_unique<GameObject>(*child);
//		newChild->m_pParent = this; // Set the parent of the new child to the copied object
//		AddChild(newChild.get());
//		scene.Add(std::move(newChild));
//	}
//}

void bew::GameObject::Update()
{
	if(!m_IsActive)
		return;

	for (auto& component : m_pComponents)
	{
		component->Update();
	}
}

void bew::GameObject::Render() const
{
	if (!m_IsActive)
		return;

	for (auto& element : m_pComponents)
	{
		element->Render();
	}
}

bew::Transform bew::GameObject::GetTransform() const
{
	return m_transform;
}

void bew::GameObject::Translate(const glm::vec3& translation)
{
	if (!m_IsActive)
		return;
	SetLocalPosition(m_LocalPosition + translation);
}

#pragma region hierargie
bew::GameObject* bew::GameObject::GetParrent() const
{
	return m_pParent;
}

void bew::GameObject::SetParrent(GameObject* pParent, bool KeepWorldPosition)
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

int bew::GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

bew::GameObject* bew::GameObject::GetChildAtIndex(int index) const
{
	return m_pChildren[index];
}

void bew::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

void bew::GameObject::RemoveChild(GameObject* child)
{
	child->SetParrent(nullptr);
}

bool bew::GameObject::IsChild(GameObject* newParent) const
{
	auto it = std::find(std::begin(m_pChildren), std::end(m_pChildren), newParent);

	return it != std::end(m_pChildren);
}
#pragma endregion

#pragma region Postion
void bew::GameObject::SetPosition(float x, float y)
{
	SetLocalPosition({ x,y,0 });

	m_transform.SetPosition(GetWorldPosition());
}

void bew::GameObject::SetPosition(const glm::vec3& pos)
{
	SetPosition(pos.x, pos.y);
}
void bew::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

glm::vec3& bew::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

///Rotation is in degrees
void bew::GameObject::SetRotation(float x)
{
	m_transform.SetRotation(x, 0, 0);
}
///Rotation is in degrees
void bew::GameObject::SetRotation(const glm::vec3& rotation)
{
	SetRotation(rotation.x);
}

void bew::GameObject::SetScale(float x, float y)
{
	m_transform.SetScale(x, y,0);
}

void bew::GameObject::SetScale(const glm::vec3& scale)
{
	SetScale(scale.x, scale.y);
}

void bew::GameObject::SetPositionDirty()
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

void bew::GameObject::UpdateWorldPosition()
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


