#include "EnemyComponent.h"
#include <iostream>
#include "BewGin.h"
#include "BezierPath.h"
#include "GameData.h"
#include "GameObject.h"
#include "GameTime.h"
#include "HealthComponent.h"
#include "HitBoxComponent.h"
#include "ObjectPoolingComponent.h"
#include "PoolComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"

std::vector<std::vector<glm::vec2>> EnemyComponent::s_Paths;

void EnemyComponent::CreatePaths()
{
	int screenWidthMid =static_cast<int>( bew::ScreenWidth * 0.4f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		glm::vec2(static_cast<float>(screenWidthMid) + 50.f,-10),
		glm::vec2(static_cast<float>(screenWidthMid) + 50.f,-20),
		glm::vec2(static_cast<float>(screenWidthMid) + 50.f,30.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 50.f,20.f) },
		1);

	path->AddCurve({
		glm::vec2(static_cast<float>(screenWidthMid) + 50.f,20.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 10.f,150.f),
		glm::vec2(75.f,180.f),
		glm::vec2(75.f,240.f) },
		20);

	path->AddCurve({
		glm::vec2(75.f,240.f),
		glm::vec2(75.f,340.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 60.f,340.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 50.f,240.f) },
		20);

	s_Paths.emplace_back();
	path->Sample(&s_Paths[currentPath]);
	delete path;

	path =  new BezierPath();

	currentPath++;
	path->AddCurve({
		glm::vec2(static_cast<float>(screenWidthMid) - 50.f,-10),
		glm::vec2(static_cast<float>(screenWidthMid) - 50.f,-20),
		glm::vec2(static_cast<float>(screenWidthMid) - 50.f,30.f),
		glm::vec2(static_cast<float>(screenWidthMid) - 50.f,20.f) },
		1);

	path->AddCurve({
		glm::vec2(static_cast<float>(screenWidthMid) - 50.f,20.f),
		glm::vec2(static_cast<float>(screenWidthMid) - 10.f,150.f),
		glm::vec2(425.f,180.f),
		glm::vec2(425.f,240.f) },
		20);

	path->AddCurve({
		glm::vec2(425.f,240.f),
		glm::vec2(425.f,340.f),
		glm::vec2(static_cast<float>(screenWidthMid) - 60.f,340.f),
		glm::vec2(static_cast<float>(screenWidthMid) - 50.f,240.f) },
		20);

	s_Paths.emplace_back();
	path->Sample(&s_Paths[currentPath]);

	delete path;
}

EnemyComponent::EnemyComponent(bew::GameObject* pParentObject)
: Component(pParentObject),m_States{new FlyIn()}, m_speed{200}
{
	m_pPlayers = GameData::GetInstance().GetPlayers();

	m_States->OnEnter(this);
}

void EnemyComponent::FixedUpdate()
{
	CheckInHitBox();
}

void EnemyComponent::Update()
{
	HandelStates();
}

void EnemyComponent::Render() const
{
#if NDEBUG
	return;
#else
	m_States->Render();
#endif
}

void EnemyComponent::HandelStates()
{
	EnemyStates* state = m_States->Update(this);

	if(state != nullptr)
	{
		m_States->OnExit(this);

		delete m_States;
		m_States = state;

		m_States->OnEnter(this);
	}
}

void EnemyComponent::CheckInHitBox()
{

	for (const auto& Player : *m_pPlayers)
	{
		std::vector<bew::GameObject*>* pBulltes = Player->GetComponent<ObjectPoolingComponent>()->GetObjectList();

		if (!pBulltes->empty())
		{
			for (const auto& bullet : *pBulltes)
			{
				auto bulletPoolComp = bullet->GetComponent<PoolComponent>();

				if (bulletPoolComp->InUse())
				{
					if (GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(bullet))
					{
						bulletPoolComp->SetInUse(false);
						bullet->SetIsActive(false);

						TakeDamages(Player);
						
					}
				}
			}
		}
	}
}

void EnemyComponent::SetFormationPosition(FormationComponent* formation,glm::vec3 posIndex)
{
	pFormation = formation;

	m_TargetPos.x = pFormation->GetParentObject()->GetWorldPosition().x + (posIndex.x * pFormation->GetGridSize().x);
	m_TargetPos.y = pFormation->GetParentObject()->GetWorldPosition().y + (posIndex.y * pFormation->GetGridSize().y);
}



void EnemyComponent::StartAndSetActive()
{
	m_States->OnEnter(this);
	GetParentObject()->SetIsActive(true);
}

EnemyComponent::~EnemyComponent()
{
	delete m_States;
	m_States = nullptr;
}
