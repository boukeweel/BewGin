#include "EnemyStates.h"

#include <glm/vec3.hpp>

#include "EnemyComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Renderer.h"

void FlyIn::OnEnter(EnemyComponent* component)
{
	m_Path = component->getPath(m_CurrentPath);
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
		return new Formation();
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

void FlyIn::OnExit(EnemyComponent*)
{
}
