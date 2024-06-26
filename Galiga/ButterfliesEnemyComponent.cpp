#include "ButterfliesEnemyComponent.h"

#include "AnimatorComponent.h"
#include "BewGin.h"
#include "BezierPath.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PoolComponent.h"
#include "ScoreComponent.h"
#include "SoundServiceLocator.h"

std::vector<std::vector<glm::vec2>> ButterfliesEnemyComponent::s_AttackingPaths;

void ButterfliesEnemyComponent::CreateAttackingPaths()
{
	int currentPath = 0;
	BezierPath* path = new BezierPath;

	path->AddCurve({
		glm::vec2(0.f,0.f),
		glm::vec2(0.f, -50.f),
		glm::vec2(-50.f,-50.f),
		glm::vec2(-50.f,0.f) },
		12);

	path->AddCurve({
		glm::vec2(-50.f,0.f),
		glm::vec2(-50.f, 75.f),
		glm::vec2(100.f,100.f),
		glm::vec2(100.f,150.f) },
		12);

	path->AddCurve({
		glm::vec2(100.f,150.f),
		glm::vec2(100.f, 190.f),
		glm::vec2(0.f,190.f),
		glm::vec2(100.f,230.f) },
		12);

	path->AddCurve({
		glm::vec2(100.f,230.f),
		glm::vec2(110.f, 235.f),
		glm::vec2(250.f,235.f),
		glm::vec2(230.f,285.f) },
		12);

	path->AddCurve({
		glm::vec2(230.f,285.f),
		glm::vec2(220.f, 325.f),
		glm::vec2(130.f,310.f),
		glm::vec2(200.f,bew::ScreenHeight + 100.f) },
		12);

	s_AttackingPaths.emplace_back();
	path->Sample(&s_AttackingPaths[currentPath]);
	delete path;
	path = new BezierPath;
	currentPath++;


	path->AddCurve({
		glm::vec2(0.f,0.f),
		glm::vec2(0.f, -50.f),
		glm::vec2(50.f,-50.f),
		glm::vec2(50.f,0.f) },
		12);

	path->AddCurve({
		glm::vec2(50.f,0.f),
		glm::vec2(50.f, 75.f),
		glm::vec2(-100.f,100.f),
		glm::vec2(-100.f,150.f) },
		12);

	path->AddCurve({
		glm::vec2(-100.f,150.f),
		glm::vec2(-100.f, 190.f),
		glm::vec2(0.f,190.f),
		glm::vec2(-100.f,230.f) },
		12);

	path->AddCurve({
		glm::vec2(-100.f,230.f),
		glm::vec2(-110.f, 235.f),
		glm::vec2(-250.f,235.f),
		glm::vec2(-230.f,285.f) },
		12);

	path->AddCurve({
		glm::vec2(-230.f,285.f),
		glm::vec2(-220.f, 325.f),
		glm::vec2(-130.f,310.f),
		glm::vec2(-200.f,bew::ScreenHeight + 100.f) },
		12);

	s_AttackingPaths.emplace_back();
	path->Sample(&s_AttackingPaths[currentPath]);
	delete path;

	//Escort paths
	currentPath++;
	path = new BezierPath;

	path->AddCurve({
		glm::vec2(0.f,0.f),
		glm::vec2(0.f, -50.f),
		glm::vec2(-50.f,-50.f),
		glm::vec2(-50.f,0.f) },
		12);

	path->AddCurve({
		glm::vec2(-50.f,0.f),
		glm::vec2(-90.f, 60.f),
		glm::vec2(-100.f,175.f),
		glm::vec2(-15.f,175.f) },
		12);

	path->AddCurve({
		glm::vec2(-15.f,175.f),
		glm::vec2(45, 175.f),
		glm::vec2(45,100.f),
		glm::vec2(-15.f,100.f) },
		12);

	path->AddCurve({
		glm::vec2(-15.f,100.f),
		glm::vec2(-80.f, 100.f),
		glm::vec2(-80.f,155.f),
		glm::vec2(-15.f,200.f) },
		12);


	path->AddCurve({
		glm::vec2(-15.f,200.f),
		glm::vec2(-10.f,200.f),
		glm::vec2(75.f,300),
		glm::vec2(75.f,350.f) },
		12);

	path->AddCurve({
		glm::vec2(75.f,350.f),
		glm::vec2(75.f,360.f),
		glm::vec2(75.f,bew::ScreenHeight + 90.f),
		glm::vec2(75.f,bew::ScreenHeight + 100.f) },
		1);



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
		12);

	path->AddCurve({
		glm::vec2(50.f,0.f),
		glm::vec2(90.f, 60.f),
		glm::vec2(100.f,175.f),
		glm::vec2(15.f,175.f) },
		12);

	path->AddCurve({
		glm::vec2(15.f,175.f),
		glm::vec2(-45, 175.f),
		glm::vec2(-45,100.f),
		glm::vec2(15.f,100.f) },
		12);

	path->AddCurve({
		glm::vec2(15.f,100.f),
		glm::vec2(80.f, 100.f),
		glm::vec2(80.f,155.f),
		glm::vec2(15.f,200.f) },
		12);


	path->AddCurve({
		glm::vec2(15.f,200.f),
		glm::vec2(10.f,200.f),
		glm::vec2(-75.f,300),
		glm::vec2(-75.f,350.f) },
		12);

	path->AddCurve({
		glm::vec2(-75.f,350.f),
		glm::vec2(-75.f,360.f),
		glm::vec2(-75.f,bew::ScreenHeight + 90.f),
		glm::vec2(-75.f,bew::ScreenHeight + 100.f) },
		1);



	s_AttackingPaths.emplace_back();
	path->Sample(&s_AttackingPaths[currentPath]);
	delete path;
}


ButterfliesEnemyComponent::ButterfliesEnemyComponent(bew::GameObject* pParentObject) : EnemyComponent(pParentObject)
{
	m_Type = EnemyTypes::Butterfly;
	m_AmountPointsDiving = 160;
	m_AmountPointsFormation = 80;
}

void ButterfliesEnemyComponent::TakeDamages(bew::GameObject * pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	if (health->GetLives() == 0)
	{
		SpawnExplosion();

		GetParentObject()->SetIsActive(false);

		bew::SoundServiceLocator::GetSoundSystem().Play(2, 1);

		//Still lock the formation when its dies while flying in
		m_pFormation->Lock();

		GetParentObject()->GetComponent<PoolComponent>()->SetInUse(false);
		health->SetLifes(1);

		int points{ m_AmountPointsFormation };
		if (m_IsDiving)
		{
			points = m_AmountPointsDiving;
		}
		pPlayer->GetComponent<ScoreComponent>()->AddScore(points);
	}
}
