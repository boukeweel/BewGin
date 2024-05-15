#include "EnemyComponent.h"
#include <iostream>
#include "BewGin.h"
#include "BezierPath.h"
#include "GameObject.h"
#include "GameTime.h"
#include "HitBoxComponent.h"
#include "ObjectPoolingComponent.h"
#include "PoolComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"

std::vector<std::vector<glm::vec2>> EnemyComponent::s_Paths;
FormationComponent* EnemyComponent::s_pFormation = nullptr;

void EnemyComponent::CreatePaths()
{
	int screenWidthMid = bew::ScreenWidth / 2;

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
		glm::vec2(50.f,180.f),
		glm::vec2(50.f,240.f) },
		20);

	path->AddCurve({
		glm::vec2(50.f,240.f),
		glm::vec2(50.f,340.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 10,340.f),
		glm::vec2(static_cast<float>(screenWidthMid),240.f) },
		20);

	s_Paths.emplace_back();
	path->Sample(&s_Paths[currentPath]);

	delete path;
}

void EnemyComponent::SetFormation(FormationComponent* formation)
{
	s_pFormation = formation;
}

EnemyComponent::EnemyComponent(bew::GameObject* pParentObject, bew::GameObject* Player, int index, int path, bool ChallangeStage)
: Component(pParentObject),m_pPlayer{ Player },m_States{new FlyIn(path)}, m_speed{200}, m_Index{index},m_ChallengeStage{ChallangeStage}
{
	
	if(m_pPlayer->HasComponent<ObjectPoolingComponent>())
	{
		m_pBulletVector = m_pPlayer->GetComponent<ObjectPoolingComponent>()->GetObjectList();
	}

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
	for (const auto& bullet : *m_pBulletVector)
	{
		auto bulletPoolComp = bullet->GetComponent<PoolComponent>();

		if (bulletPoolComp->InUse())
		{
			if (GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(bullet))
			{
				bulletPoolComp->SetInUse(false);
				bullet->SetIsActive(false);

				GetParentObject()->SetIsActive(false);

				m_pPlayer->GetComponent<ScoreComponent>()->AddScore(100);
			}
		}
	}
}

EnemyComponent::~EnemyComponent()
{
	delete m_States;
	m_States = nullptr;
}
