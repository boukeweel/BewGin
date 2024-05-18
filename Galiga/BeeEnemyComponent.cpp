#include "BeeEnemyComponent.h"

#include <iostream>

BeeEnemyComponent::BeeEnemyComponent(bew::GameObject* pParentObject, int index, int path, bool ChallengeStage)
: EnemyComponent(pParentObject,index,path,ChallengeStage)
{
	if(!m_ChallengeStage)
	{
		m_TargetPos = GetFormationPosition();
	}
}

glm::vec3 BeeEnemyComponent::GetFormationPosition()
{
	//this is taken form a video By Ather omar
	glm::vec3 offset{};

	//set intial grid offset to the enemies adding the offset * 2 again than * it by m_index / 4 what is on purpose a int devision and than alternating left and right with the pow
	offset.x = (s_pFormation->GetGridSize().x + s_pFormation->GetGridSize().x * 2 * (static_cast<float>(m_Index / 4))) * std::powf(-1, static_cast<float>(m_Index % 2 + 1));
	offset.y = s_pFormation->GetGridSize().y * (static_cast<float>((m_Index % 4) / 2));

	return offset;
}
