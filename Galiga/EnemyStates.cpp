#include "EnemyStates.h"

#include <glm/vec3.hpp>

#include "EnemyComponent.h"
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

#pragma region Attacking bee

void AttackingBee::OnEnter(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetParrent(nullptr, true);

	m_Path = component->GetAttackingPath(component->GetAttackingPathIndex());

	m_DiveStartPos = parentObject->GetWorldPosition();
	m_CurrentWayPoint = 1;
}

EnemyStates* AttackingBee::Update(EnemyComponent* component)
{
	//I feel like this is wack but it looks so mutch more smooth
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


void AttackingBee::Render() const
{
	//just for debug
	for (size_t i = 0; i < m_Path->size() - 1; ++i)
	{
		bew::Renderer::GetInstance().DrawLine(m_DiveStartPos.x + (*m_Path)[i].x, m_DiveStartPos.y + (*m_Path)[i].y, m_DiveStartPos.x +  (*m_Path)[i + 1].x, m_DiveStartPos.y + (*m_Path)[i + 1].y);
	}
}

#pragma endregion

#pragma region Attacking Butterly
void AttackingButterFly::OnEnter(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetParrent(nullptr, true);

	m_Path = component->GetAttackingPath(component->GetAttackingPathIndex());

	m_DiveStartPos = parentObject->GetWorldPosition();
	m_CurrentWayPoint = 1;
}

EnemyStates* AttackingButterFly::Update(EnemyComponent* component)
{
	//I feel like this is wack but it looks so mutch more smooth
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


void AttackingButterFly::Render() const
{
	//just for debug
	for (size_t i = 0; i < m_Path->size() - 1; ++i)
	{
		bew::Renderer::GetInstance().DrawLine(m_DiveStartPos.x + (*m_Path)[i].x, m_DiveStartPos.y + (*m_Path)[i].y, m_DiveStartPos.x + (*m_Path)[i + 1].x, m_DiveStartPos.y + (*m_Path)[i + 1].y);
	}
}

#pragma endregion

#pragma region Attacking boss

void AttackingBoss::OnEnter(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetParrent(nullptr, true);

	m_Path = component->GetAttackingPath(component->GetAttackingPathIndex());

	m_DiveStartPos = parentObject->GetWorldPosition();
	m_CurrentWayPoint = 1;
}

EnemyStates* AttackingBoss::Update(EnemyComponent* component)
{
	//I feel like this is wack but it looks so mutch more smooth
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


void AttackingBoss::Render() const
{
	//just for debug
	for (size_t i = 0; i < m_Path->size() - 1; ++i)
	{
		bew::Renderer::GetInstance().DrawLine(m_DiveStartPos.x + (*m_Path)[i].x, m_DiveStartPos.y + (*m_Path)[i].y, m_DiveStartPos.x + (*m_Path)[i + 1].x, m_DiveStartPos.y + (*m_Path)[i + 1].y);
	}
}

#pragma endregion

