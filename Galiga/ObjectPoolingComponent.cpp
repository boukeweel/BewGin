#include "ObjectPoolingComponent.h"

#include "ObjectPreset.h"
#include "Scene.h"
#include "SceneManager.h"

ObjectPoolingComponent::ObjectPoolingComponent(bew::GameObject* pParentObject, ObjectPreset* object, int amount) : Component(pParentObject),m_BaseObject{object},m_MaxCurrentObjects{ amount}
{
	CreateObjects(amount);
}

void ObjectPoolingComponent::CreateObjects(int amount)
{
	auto& scene = bew::SceneManager::GetInstance().GetCurrentScene();

	for (int i = 0; i < amount; ++i)
	{
		auto newobj = m_BaseObject->Create();
		newobj->SetIsActive(false);

		newobj->SetParrent(GetParentObject());

		m_Objects.emplace_back(newobj.get());

		scene.Add(std::move(newobj));
	}
}
