#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject()
{
	delete m_pParent;

	for (auto childs : m_pChildren)
	{
		delete childs;
	}

	m_pParent = nullptr;
	m_pChildren.empty();
}




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

dae::GameObject* dae::GameObject::GetParrent() const
{
	return m_pParent;
}

void dae::GameObject::SetParrent(GameObject* pParent)
{
	if(m_pParent == pParent || pParent == this || IsChild(pParent))
	{
		//todo make a trow with custom expetion error
		return;
	}

	if(m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = pParent;
	if(m_pParent)
	{
		m_pParent->AddChild(this);
	}

	//todo update position rotation and scale
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
	m_pChildren.push_back(child);
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

