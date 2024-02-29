#include "Component.h"

dae::Component::Component(GameObject* pparentObject) :m_pParentObject{ pparentObject }
{
}

dae::Component::~Component()
{
}

dae::GameObject* dae::Component::GetParentObject() const
{
	return m_pParentObject;
}
