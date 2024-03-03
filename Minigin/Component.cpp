#include "Component.h"

dae::Component::Component(GameObject* pparentObject) :m_pParentObject{ pparentObject }
{
}

dae::Component::~Component()
{
}

void dae::Component::Update(float /*deltaTime*/)
{
}

dae::GameObject* dae::Component::GetParentObject() const
{
	return m_pParentObject;
}
