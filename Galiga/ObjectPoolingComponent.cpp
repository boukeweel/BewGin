#include "ObjectPoolingComponent.h"
#include "ObjectPreset.h"
#include "PoolComponent.h"
#include "Scene.h"
#include "SceneManager.h"

ObjectPoolingComponent::ObjectPoolingComponent(bew::GameObject* pParentObject,std::unique_ptr<ObjectPreset>  object, int amount)
: Component(pParentObject),m_BaseObject{std::move(object)}
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

		m_Objects.emplace_back(newobj.get());

		scene.Add(std::move(newobj));
	}

	m_POOLSIZE += amount;
}

void ObjectPoolingComponent::SetNextObjectActive()
{
	SetNextObjectActive(GetParentObject()->GetWorldPosition());
}

void ObjectPoolingComponent::SetNextObjectActive(glm::vec3 pos)
{
	m_Currentobj++;

	if (m_Currentobj == m_POOLSIZE)
	{
		CreateObjects(5);
	}

	for (m_Currentobj = 0; m_Currentobj < m_POOLSIZE; ++m_Currentobj)
	{
		auto poolcomponent = m_Objects[m_Currentobj]->GetComponent<PoolComponent>();
		if (poolcomponent->InUse() == false)
		{
			poolcomponent->SetInUse(true);
			break;
		}
	}

	m_Objects[m_Currentobj]->SetPosition(pos);
	m_Objects[m_Currentobj]->SetIsActive(true);
}



