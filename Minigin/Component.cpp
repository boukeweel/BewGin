#include "Component.h"

bew::Component::Component(GameObject* pparentObject) :m_pParentObject{ pparentObject }
{
}
bew::GameObject* bew::Component::GetParentObject() const
{
	return m_pParentObject;
}
