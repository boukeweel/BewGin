#include "ObjectPoolingComponent.h"

#include "GameObject.h"

ObjectPoolingComponent::ObjectPoolingComponent(bew::GameObject* pParentObject, bew::GameObject* object, int amount) : Component(pParentObject),m_BaseObject{object},m_MaxCurrentObjects{ amount}
{
	CreateObjects(amount);
}

void ObjectPoolingComponent::CreateObjects(int amout)
{
	for (int i = 0; i < amout; ++i)
	{
		auto newobj = std::make_unique<bew::GameObject>(*m_BaseObject);

		m_Objects.emplace_back()
	}
}
