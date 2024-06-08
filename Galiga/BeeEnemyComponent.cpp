#include "BeeEnemyComponent.h"

#include "AnimatorComponent.h"
#include "BezierPath.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PoolComponent.h"
#include "ScoreComponent.h"
#include "SoundServiceLocator.h"

std::vector<std::vector<glm::vec2>> BeeEnemyComponent::s_AttackingPaths;
void BeeEnemyComponent::CreateAttackingPaths()
{
	int currentPath = 0;
	BezierPath* path = new BezierPath;

	path->AddCurve({
		glm::vec2(0.f,0.f),
		glm::vec2(0.f, -50.f),
		glm::vec2(-50.f,-50.f),
		glm::vec2(-50.f,0.f) },
		15);

	path->AddCurve({
		glm::vec2(-50.f,0.f),
		glm::vec2(-50.f,50.f),
		glm::vec2(0.f,75.f),
		glm::vec2(50.f,75.f) },
		15);

	path->AddCurve({
		glm::vec2(50.f,75.f),
		glm::vec2(200.f, 70.f),
		glm::vec2(250.f,100.f),
		glm::vec2(250.f,250.f) },
		15);

	path->AddCurve({
		glm::vec2(250.f,250.f),
		glm::vec2(250.f, 350.f),
		glm::vec2(100.f,350.f),
		glm::vec2(100.f,250.f) },
		15);

	s_AttackingPaths.emplace_back();
	path->Sample(&s_AttackingPaths[currentPath]);
	delete path;

	currentPath++;

	path = new BezierPath;

	path->AddCurve({
		glm::vec2(0.f,0.f),
		glm::vec2(0.f, -50.f),
		glm::vec2(50.f,-50.f),
		glm::vec2(50.f,0.f) },
		15);

	path->AddCurve({
		glm::vec2(50.f,0.f),
		glm::vec2(50.f, 50.f),
		glm::vec2(0.f,75.f),
		glm::vec2(-50.f,75.f) },
		15);

	path->AddCurve({
		glm::vec2(-50.f,75.f),
		glm::vec2(-200.f, 70.f),
		glm::vec2(-250.f,100.f),
		glm::vec2(-250.f,250.f) },
		15);

	path->AddCurve({
		glm::vec2(-250.f,250.f),
		glm::vec2(-250.f, 350.f),
		glm::vec2(-100.f,350.f),
		glm::vec2(-100.f,250.f) },
		15);

	s_AttackingPaths.emplace_back();
	path->Sample(&s_AttackingPaths[currentPath]);
	delete path;
}

BeeEnemyComponent::BeeEnemyComponent(bew::GameObject* pParentObject)
: EnemyComponent(pParentObject)
{
	m_Type = EnemyTypes::Bee;
	m_AmountPointsDiving = 100;
	m_AmountPointsFormation = 50;
}

void BeeEnemyComponent::TakeDamages(bew::GameObject* pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	if (health->GetLives() == 0)
	{
		SpawnExplosion();

		GetParentObject()->SetIsActive(false);

		bew::SoundServiceLocator::GetSoundSystem().Play(1, 1);

		//Still lock the formation when its dies while flying in
		m_pFormation->Lock();

		GetParentObject()->GetComponent<PoolComponent>()->SetInUse(false);
		health->SetLifes(1);
		int points{m_AmountPointsFormation};
		if(m_IsDiving)
		{
			points = m_AmountPointsDiving;
		}
		pPlayer->GetComponent<ScoreComponent>()->AddScore(points);
	}
}
