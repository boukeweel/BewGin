#include "EnemyComponent.h"
#include <iostream>

#include "AnimatorComponent.h"
#include "BewGin.h"
#include "BezierPath.h"
#include "BulletComponent.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "GameTime.h"
#include "HealthComponent.h"
#include "HitBoxComponent.h"
#include "BulletPool.h"
#include "GameData.h"
#include "PoolComponent.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "ScoreComponent.h"

std::vector<std::vector<glm::vec2>> EnemyComponent::s_FormationPaths;

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

	s_FormationPaths.emplace_back();
	path->Sample(&s_FormationPaths[currentPath]);
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

	s_FormationPaths.emplace_back();
	path->Sample(&s_FormationPaths[currentPath]);
	delete path;

	path = new BezierPath();

	currentPath++;

	path->AddCurve({
		glm::vec2(0,static_cast<float>(bew::ScreenHeight)),
		glm::vec2(0,static_cast<float>(bew::ScreenHeight) + 10.f),
		glm::vec2(100.f,static_cast<float>(bew::ScreenHeight) - 110.f),
		glm::vec2(100.f,static_cast<float>(bew::ScreenHeight) - 100.f) },
		1);

	path->AddCurve({
		glm::vec2(100.f,static_cast<float>(bew::ScreenHeight) - 100.f),
		glm::vec2(200.f,static_cast<float>(bew::ScreenHeight) - 450.f),
		glm::vec2(-125.f,static_cast<float>(bew::ScreenHeight) + 50.f ),
		glm::vec2(static_cast<float>(screenWidthMid) - 15.f,225.f) },
		30);

	s_FormationPaths.emplace_back();
	path->Sample(&s_FormationPaths[currentPath]);
	delete path;

	path = new BezierPath();

	currentPath++;

	path->AddCurve({
		glm::vec2(static_cast<float>(bew::ScreenWidth) - 150.f,static_cast<float>(bew::ScreenHeight)),
		glm::vec2(static_cast<float>(bew::ScreenWidth) - 150.f,static_cast<float>(bew::ScreenHeight) + 10.f),
		glm::vec2(static_cast<float>(bew::ScreenWidth) - 250.f,static_cast<float>(bew::ScreenHeight) - 110.f),
		glm::vec2(static_cast<float>(bew::ScreenWidth) - 250.f,static_cast<float>(bew::ScreenHeight) - 100.f) },
		1);

	path->AddCurve({
		glm::vec2(static_cast<float>(bew::ScreenWidth) - 250.f,static_cast<float>(bew::ScreenHeight) - 100.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 100.f,100.f),
		glm::vec2(static_cast<float>(bew::ScreenWidth) + 50.f,static_cast<float>(bew::ScreenHeight) + 50.f),
		glm::vec2(static_cast<float>(screenWidthMid) + 15.f,240.f) },
		30);

	s_FormationPaths.emplace_back();
	path->Sample(&s_FormationPaths[currentPath]);
	delete path;
}

EnemyComponent::EnemyComponent(bew::GameObject* pParentObject)
: Component(pParentObject),m_pStates{new FlyIn()}, m_speed{400}
{
	m_pPlayers = GameEntityData::GetInstance().GetPlayers();

	CreateBullet();
}

void EnemyComponent::CreateBullet()
{
	BulletPreset bulletPreset;
	auto bullet = bulletPreset.Create();
	auto bulletcomp = bullet->GetComponent<BulletComponent>();
	bulletcomp->SetDirection({ 0,1,0 });
	bulletcomp->SetResetHeight(bew::ScreenHeight + 10.f);
	bulletcomp->SetSpeed(300.f);
	bullet->SetRotation(180.f);
	m_pBullet = bullet.get();
	bullet->SetIsActive(false);
	bew::SceneManager::GetInstance().AddToCurrentScene(std::move(bullet));
}

void EnemyComponent::ResetEnemy()
{
	delete m_pStates;
	m_pStates = new FlyIn;
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
	m_pStates->Render();
#endif
}

void EnemyComponent::HandelStates()
{
	EnemyStates* state = m_pStates->Update(this);

	if(state != nullptr)
	{
		m_pStates->OnExit(this);

		delete m_pStates;
		m_pStates = state;

		m_pStates->OnEnter(this);
	}
}

void EnemyComponent::Shoot()
{
	m_pBullet->SetPosition(GetParentObject()->GetWorldPosition());
	m_pBullet->SetIsActive(true);
}

void EnemyComponent::CheckInHitBox()
{
	for (const auto& Player : *m_pPlayers)
	{
		//collsion Bullets
		std::vector<bew::GameObject*>* pBulltes = Player->GetComponent<BulletPool>()->GetObjectList();

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
						GameData::GetInstance().ShotHit();
						TakeDamages(Player);
					}
				}
			}
		}
	}
}

void EnemyComponent::SpawnExplosion()
{
	auto explosion = GameEntityData::GetInstance().GetExplosion();
	explosion->SetPosition(GetParentObject()->GetWorldPosition());
	explosion->GetComponent<bew::AnimatorComponent>()->PlayCurrentAmation();
}

void EnemyComponent::SetFormationPosition(FormationComponent* formation,glm::vec3 posIndex)
{
	m_pFormation = formation;
	m_PositionIndex = posIndex;
}

glm::vec3 EnemyComponent::GetFormationTargetPosition() const
{
	glm::vec3 targetPos;
	targetPos.x = m_pFormation->GetParentObject()->GetWorldPosition().x + (m_PositionIndex.x * m_pFormation->GetGridSize().x);
	targetPos.y = m_pFormation->GetParentObject()->GetWorldPosition().y + (m_PositionIndex.y * m_pFormation->GetGridSize().y);
	targetPos.z = 0;
	return targetPos;
}

void EnemyComponent::StartAndSetActive()
{
	m_pStates->OnEnter(this);
	GetParentObject()->SetIsActive(true);
}

void EnemyComponent::SetAbleToAttack(bool ableToAttack)
{
	m_AbleToAttack = ableToAttack;
	SetAttackingPath(m_AttackSide);
}

EnemyComponent::~EnemyComponent()
{
	delete m_pStates;
	m_pStates = nullptr;
}
