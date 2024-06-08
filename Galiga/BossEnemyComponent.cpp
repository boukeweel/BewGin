#include "BossEnemyComponent.h"

#include "AnimatorComponent.h"
#include "BewGin.h"
#include "BezierPath.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PoolComponent.h"
#include "RandomFunctions.h"
#include "ScoreComponent.h"
#include "SoundServiceLocator.h"
#include "SpriteSheetComponent.h"

std::vector<std::vector<glm::vec2>> BossEnemyComponent::s_AttackingPaths;

void BossEnemyComponent::CreateAttackingPaths()
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
		glm::vec2(75.f,bew::ScreenHeight  + 100.f) },
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
		glm::vec2(100.f,180.f),
		glm::vec2(100.f,250.f) },
		12);

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
	glm::vec2(-100.f,180.f),
	glm::vec2(-100.f,250.f) },
	12);

	s_AttackingPaths.emplace_back();
	path->Sample(&s_AttackingPaths[currentPath]);
	delete path;
}

BossEnemyComponent::BossEnemyComponent(bew::GameObject* pParentObject, CaptureBeamComponent* captureBeam) : EnemyComponent(pParentObject),m_CaptureBeam{captureBeam}
{
	m_Type = EnemyTypes::Boss;
	m_AmountPointsDiving = 400;
	m_AmountPointsFormation = 150;
}

void BossEnemyComponent::ResetEnemy()
{
	delete m_pStates;
	m_pStates = new FlyIn;
	m_pStates->OnEnter(this);
	GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSprite(0, 0);
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->SwitchAnimation(0, true);
	GetParentObject()->GetComponent<HealthComponent>()->SetLifes(2);
}

void BossEnemyComponent::SetAbleToAttack(bool ableToAttack)
{
	m_AbleToAttack = ableToAttack;
	
	int path = m_AttackSide;
	//random path
	const int rnd = bew::RandomFunctions::RandomI(0, 2);
	if(rnd == 2)
	{
		path += 2;
	}
	SetAttackingPath(path);
}

void BossEnemyComponent::TakeDamages(bew::GameObject* pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSprite(1, 0);
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->SwitchAnimation(1 ,true);

	if (health->GetLives() == 0)
	{
		SpawnExplosion();

		bew::SoundServiceLocator::GetSoundSystem().Play(5, 1);

		//set all children to false
		GetParentObject()->SetIsActive(false);
		for (int i = 0; i < GetParentObject()->GetChildCount(); ++i)
		{
			GetParentObject()->GetChildAtIndex(i)->SetIsActive(false);
		}

		//Still lock the formation when its dies while flying in
		m_pFormation->Lock();

		GetParentObject()->GetComponent<PoolComponent>()->SetInUse(false);

		int points{ m_AmountPointsFormation };
		if (m_IsDiving)
		{
			points = m_AmountPointsDiving;
		}
		pPlayer->GetComponent<ScoreComponent>()->AddScore(points);

	}
	else
	{
		bew::SoundServiceLocator::GetSoundSystem().Play(4, 1);
	}
}
