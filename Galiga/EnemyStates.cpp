#include "EnemyStates.h"

#include <glm/vec3.hpp>

#include "AnimatorComponent.h"
#include "BewGin.h"
#include "EnemyComponent.h"
#include "GameData.h"
#include "GameObject.h"
#include "GameTime.h"
#include "InputManager.h"
#include "Renderer.h"

#pragma region Fly in 

void FlyIn::OnEnter(EnemyComponent* component)
{
	m_Path = component->GetFormationPath(component->GetCurrentFormationPath());
	component->GetParentObject()->SetPosition((*m_Path)[m_CurrentWayPoint].x, (*m_Path)[m_CurrentWayPoint].y);
}

EnemyStates* FlyIn::Update(EnemyComponent* component)
{
	glm::vec3 CheckPos{
		(*m_Path)[m_CurrentWayPoint].x - component->GetParentObject()->GetWorldPosition().x,
		(*m_Path)[m_CurrentWayPoint].y - component->GetParentObject()->GetWorldPosition().y,
		component->GetParentObject()->GetWorldPosition().z };
	float distance = glm::length(CheckPos);

	if (distance < m_Epsilon)
	{
		m_CurrentWayPoint++;
	}
	if (m_CurrentWayPoint < static_cast<int>(m_Path->size()))
	{
		const glm::vec2 nextWaypoint = (*m_Path)[m_CurrentWayPoint];
		const glm::vec2 dist = nextWaypoint - glm::vec2(component->GetParentObject()->GetWorldPosition().x, component->GetParentObject()->GetWorldPosition().y);
		const glm::vec2 velocity = glm::normalize(dist);

		component->GetParentObject()->Translate(glm::vec3(velocity, 0.0f) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());

		component->GetParentObject()->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

		return nullptr;
	}
	else
	{
		if (component->GetIsChallengeStage())
			return new AttackingBee();
		else
			return new FlyToFormationPosition();
	}
}

void FlyIn::Render() const
{
	//just for debug
	for (size_t i = 0; i < m_Path->size() - 1; ++i)
	{
		bew::Renderer::GetInstance().DrawLine((*m_Path)[i].x, (*m_Path)[i].y, (*m_Path)[i + 1].x, (*m_Path)[i + 1].y);
	}
}

#pragma endregion

#pragma region Fly To Formation

EnemyStates* FlyToFormationPosition::Update(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };

	glm::vec3 targetpos = component->GetFormationTargetPosition();
	glm::vec3 dist = targetpos - parentObject->GetWorldPosition();
	parentObject->Translate(glm::normalize(dist) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());

	parentObject->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

	if (glm::length(dist) < m_Epsilon)
		return new Formation;

	return nullptr;
}

void FlyToFormationPosition::OnExit(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetPosition(component->GetFormationTargetPosition());
	parentObject->SetRotation(0);
	parentObject->SetParrent(component->GetFormation()->GetParentObject(), true);

	component->GetFormation()->Lock();
	component->SetAbleToAttack(false);
}

#pragma endregion

#pragma region Formation

EnemyStates* Formation::Update(EnemyComponent* component)
{
	if(component->GetFormation()->GetIsLocked() && component->GetAbleToAttack())
	{
		switch (component->GetEnemyType())
		{
		case EnemyComponent::EnemyTypes::Bee:
			return new AttackingBee;
			break;
		case EnemyComponent::EnemyTypes::Butterfly:
			return new AttackingButterFly;
			break;
		case EnemyComponent::EnemyTypes::Boss:
			return new AttackingBoss;
			break;
		}
	}
	return nullptr;
}

#pragma endregion

#pragma region Attacking Base

EnemyStates* Attacking::Update(EnemyComponent* component)
{
	glm::vec3 CheckPos{
		(m_DiveStartPos.x + (*m_Path)[m_CurrentWayPoint].x) - component->GetParentObject()->GetWorldPosition().x,
		(m_DiveStartPos.y + (*m_Path)[m_CurrentWayPoint].y) - component->GetParentObject()->GetWorldPosition().y,
		component->GetParentObject()->GetWorldPosition().z };
	float distance = glm::length(CheckPos);

	if (distance < m_Epsilon)
	{
		m_CurrentWayPoint++;
	}

	if (m_CurrentWayPoint < static_cast<int>(m_Path->size()))
	{
		const glm::vec2 wayPointPosition = m_DiveStartPos + (*m_Path)[m_CurrentWayPoint];

		const glm::vec2 dist = wayPointPosition - glm::vec2(component->GetParentObject()->GetWorldPosition().x, component->GetParentObject()->GetWorldPosition().y);
		const glm::vec2 velocity = glm::normalize(dist);

		component->GetParentObject()->Translate(glm::vec3(velocity, 0.0f) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());

		component->GetParentObject()->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

		return nullptr;
	}
	else
	{
		return new FlyToFormationPosition;
	}
}

void Attacking::Render() const
{
	//just for debug
	if(m_Path != nullptr)
	{
		for (size_t i = 0; i < m_Path->size() - 1; ++i)
		{
			bew::Renderer::GetInstance().DrawLine(m_DiveStartPos.x + (*m_Path)[i].x, m_DiveStartPos.y + (*m_Path)[i].y, m_DiveStartPos.x + (*m_Path)[i + 1].x, m_DiveStartPos.y + (*m_Path)[i + 1].y);
		}
	}
}

#pragma endregion

#pragma region Attacking bee

void AttackingBee::OnEnter(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetParrent(nullptr, true);

	m_Path = component->GetAttackingPath(component->GetAttackingPathIndex());

	m_DiveStartPos = parentObject->GetWorldPosition();
	component->SetIsDiving(true);
}

void AttackingBee::OnExit(EnemyComponent* component)
{
	component->SetIsDiving(false);
}
#pragma endregion

#pragma region Attacking Butterly
void AttackingButterFly::OnEnter(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetParrent(nullptr, true);

	m_Path = component->GetAttackingPath(component->GetAttackingPathIndex());

	m_DiveStartPos = parentObject->GetWorldPosition();
	component->SetIsDiving(true);
}

void AttackingButterFly::OnExit(EnemyComponent* component)
{
	component->SetIsDiving(false);
	component->GetParentObject()->SetPosition(m_DiveStartPos.x,-100);
}

#pragma endregion

#pragma region Attacking boss

void AttackingBoss::OnEnter(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetParrent(nullptr, true);

	int attackPath = component->GetAttackingPathIndex();
	m_Path = component->GetAttackingPath(attackPath);

	m_DiveStartPos = parentObject->GetWorldPosition();
	component->SetIsDiving(true);

	if(attackPath < 2)
	{
		FindEscoretButterFlies(component);
		m_BeamAttack = false;
	}
	else
	{
		m_BeamAttack = true;
	}
}



void AttackingBoss::FindEscoretButterFlies(EnemyComponent* component)
{
	glm::vec3 posindex = component->GetPosIndex();

	std::vector<bew::GameObject*>* enemies = GameData::GetInstance().GetEnemies();

	std::vector<bew::GameObject*> foundEnemies;

	for (auto* enemy : *enemies)
	{
		glm::vec3 enemyPos = enemy->GetComponent<EnemyComponent>()->GetPosIndex();

		//only check the row below the bosses
		if (enemyPos.y != posindex.y + 1)
		{
			continue;
		}

		if (enemyPos.x == posindex.x)
		{
			foundEnemies.push_back(enemy);
		}
		else if (posindex.x <= 5 && enemyPos.x == posindex.x - 1)
		{
			foundEnemies.push_back(enemy);
		}
		else if (posindex.x > 5 && enemyPos.x == posindex.x + 1)
		{
			foundEnemies.push_back(enemy);
		}
		if (foundEnemies.size() == 2)
		{
			break;
		}
	}

	for (auto found_enemy : foundEnemies)
	{
		auto enemycomp = found_enemy->GetComponent<EnemyComponent>();
		if (enemycomp->GetIsDiving() == false)
		{
			enemycomp->SetAbleToAttack(true);
			enemycomp->SetAttackingPath(component->GetAttackingPathIndex() + 2);
		}
	}
}


EnemyStates* AttackingBoss::Update(EnemyComponent* component)
{
	glm::vec3 CheckPos{
		(m_DiveStartPos.x + (*m_Path)[m_CurrentWayPoint].x) - component->GetParentObject()->GetWorldPosition().x,
		(m_DiveStartPos.y + (*m_Path)[m_CurrentWayPoint].y) - component->GetParentObject()->GetWorldPosition().y,
		component->GetParentObject()->GetWorldPosition().z };
	float distance = glm::length(CheckPos);

	if (distance < m_Epsilon)
	{
		m_CurrentWayPoint++;
	}

	if (m_CurrentWayPoint < static_cast<int>(m_Path->size()))
	{
		const glm::vec2 wayPointPosition = m_DiveStartPos + (*m_Path)[m_CurrentWayPoint];

		const glm::vec2 dist = wayPointPosition - glm::vec2(component->GetParentObject()->GetWorldPosition().x, component->GetParentObject()->GetWorldPosition().y);
		const glm::vec2 velocity = glm::normalize(dist);

		component->GetParentObject()->Translate(glm::vec3(velocity, 0.0f) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());

		component->GetParentObject()->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

		return nullptr;
	}
	else
	{
		if(m_BeamAttack)
		{
			return new AttackingBossBeam;
		}
		else
		{
			return new FlyToFormationPosition;
		}
		
	}
}

void AttackingBoss::OnExit(EnemyComponent* component)
{
	if(!m_BeamAttack)
	{
		component->SetIsDiving(false);
		component->GetParentObject()->SetPosition(m_DiveStartPos.x, -100);
	}
}

void AttackingBossBeam::OnEnter(EnemyComponent* component)
{
	m_Capturing = true;
	component->GetParentObject()->SetRotation(180.f);
	m_DiveStartPos = component->GetFormationTargetPosition();
	component->GetCaptureBeam()->GetParentObject()->SetIsActive(true);
	component->GetCaptureBeam()->StartCapturing();
}

EnemyStates* AttackingBossBeam::Update(EnemyComponent* component)
{
	if(m_Capturing)
	{
		auto beam = component->GetCaptureBeam();
		if(beam->GetFinsihed())
		{
			m_Capturing = false;
		}

		return nullptr;
	}
	else
	{
		glm::vec2 endPoint;
		endPoint.x = component->GetParentObject()->GetWorldPosition().x;
		endPoint.y = bew::ScreenHeight + 100;

		const glm::vec2 dist = endPoint - glm::vec2(component->GetParentObject()->GetWorldPosition().x, component->GetParentObject()->GetWorldPosition().y);
		const glm::vec2 velocity = glm::normalize(dist);

		component->GetParentObject()->Translate(glm::vec3(velocity, 0.0f) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());
		component->GetParentObject()->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

		if (glm::length(dist) < m_Epsilon)
		{
			return new FlyToFormationPosition;
		}

		return nullptr;
	}
}

void AttackingBossBeam::OnExit(EnemyComponent* component)
{
	component->SetIsDiving(false);
	component->GetParentObject()->SetPosition(m_DiveStartPos.x,-100);
	component->GetCaptureBeam()->GetParentObject()->SetIsActive(false);
	component->GetCaptureBeam()->ResetBeam();
}

#pragma endregion


