#include "BulletPool.h"

#include "GameData.h"
#include "ObjectPreset.h"
#include "PoolComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SoundServiceLocator.h"

BulletPool::BulletPool(bew::GameObject* pParentObject, int amount, glm::vec3 posOfset)
: Component(pParentObject),m_pBaseObject{std::make_unique<BulletPreset>()},m_PosOfset(posOfset)
{
	CreateObjects(amount);
}
void BulletPool::CreateObjects(int amount)
{
	auto& SceneManger = bew::SceneManager::GetInstance();

	for (int i = 0; i < amount; ++i)
	{
		auto newobj = m_pBaseObject->Create();
		newobj->SetIsActive(false);

		m_pBullets.emplace_back(newobj.get());

		SceneManger.AddToCurrentScene(std::move(newobj));
	}

	m_POOLSIZE += amount;
}

void BulletPool::SetNextObjectActive()
{
	SetNextObjectActive(GetParentObject()->GetWorldPosition() + m_PosOfset);
}

void BulletPool::SetNextObjectActive(glm::vec3 pos)
{
	int startingObj = m_Currentobj;

	do {
		m_Currentobj = (m_Currentobj + 1) % m_POOLSIZE;

		auto poolcomponent = m_pBullets[m_Currentobj]->GetComponent<PoolComponent>();
		if (!poolcomponent->InUse())
		{
			poolcomponent->SetInUse(true);
			m_pBullets[m_Currentobj]->SetPosition(pos);
			m_pBullets[m_Currentobj]->SetIsActive(true);
			bew::SoundServiceLocator::GetSoundSystem().Play(0, 10);
			GameData::GetInstance().FireShot();
			return;
		}
	} while (m_Currentobj != startingObj);
}



