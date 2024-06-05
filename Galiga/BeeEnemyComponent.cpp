#include "BeeEnemyComponent.h"

#include "AnimatorComponent.h"
#include "BezierPath.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PoolComponent.h"
#include "ScoreComponent.h"

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
}

void BeeEnemyComponent::TakeDamages(bew::GameObject* pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	if (health->GetLives() == 0)
	{
		auto explosion = GameEntityData::GetInstance().GetExplosion();
		explosion->SetPosition(GetParentObject()->GetWorldPosition());
		explosion->GetComponent<bew::AnimatorComponent>()->PlayCurrentAmation();

		GetParentObject()->SetIsActive(false);

		//this is not good but could not think of something else
		m_pFormation->Lock();

		GetParentObject()->GetComponent<PoolComponent>()->SetInUse(false);
		health->SetLifes(1);
		pPlayer->GetComponent<ScoreComponent>()->AddScore(m_AmountPoints);
	}
}
