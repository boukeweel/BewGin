#include "EnemyStates.h"

#include <glm/vec3.hpp>

#include "EnemyComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Renderer.h"

FlyIn::FlyIn()
{}

void FlyIn::OnEnter(EnemyComponent* component)
{
	m_Path = component->getPath(component->GetCurrentPath());
	component->GetParentObject()->SetPosition((*m_Path)[m_CurrentWayPoint].x, (*m_Path)[m_CurrentWayPoint].y);
}

EnemyStates* FlyIn::Update(EnemyComponent* component)
{
	glm::vec3 CheckPos{
		(*m_Path)[m_CurrentWayPoint].x - component->GetParentObject()->GetWorldPosition().x,
		(*m_Path)[m_CurrentWayPoint].y - component->GetParentObject()->GetWorldPosition().y,
		component->GetParentObject()->GetWorldPosition().z };
	float distance = glm::length(CheckPos);

	if (distance < EPSILON)
	{
		m_CurrentWayPoint++;
	}
	if (m_CurrentWayPoint < static_cast<int>(m_Path->size()))
	{
		glm::vec2 nextWaypoint = (*m_Path)[m_CurrentWayPoint];
		glm::vec2 dist = nextWaypoint - glm::vec2(component->GetParentObject()->GetWorldPosition().x, component->GetParentObject()->GetWorldPosition().y);
		glm::vec2 velocity = glm::normalize(dist);

		component->GetParentObject()->Translate(glm::vec3(velocity, 0.0f) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());

		component->GetParentObject()->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

		return nullptr;
	}
	else
	{
		if (component->GetIsChallengeStage())
			return new Attacking();
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


EnemyStates* FlyToFormationPosition::Update(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };

	glm::vec3 targetpos = FlyInTargetPosition(component);
	glm::vec3 dist = targetpos - parentObject->GetWorldPosition();
	parentObject->Translate(glm::normalize(dist) * bew::GameTime::GetDeltaTimeFloat() * component->GetSpeed());

	parentObject->SetRotation(atan2(dist.y, dist.x) * (180.f / 3.14f) + 90);

	if (glm::length(dist) < EPSILON)
		return new Formation;

	return nullptr;
}

void FlyToFormationPosition::OnExit(EnemyComponent* component)
{
	auto parentObject{ component->GetParentObject() };
	parentObject->SetPosition(FlyInTargetPosition(component));
	parentObject->SetRotation(0);
	parentObject->SetParrent(component->GetFormation()->GetParentObject(), true);
}

glm::vec3 FlyToFormationPosition::FlyInTargetPosition(EnemyComponent* component)
{
	return component->GetTargetPos();
}

EnemyStates* Formation::Update(EnemyComponent* /*component*/)
{
	//component->GetParentObject()->SetPosition(glm::vec3(component->SetFormationPosition(), 0));

	return nullptr;
}
