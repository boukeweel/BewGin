#pragma once
#include "EnemyComponent.h"
class BeeEnemyComponent :
    public EnemyComponent
{
public:
    BeeEnemyComponent(bew::GameObject* pParentObject, int index, int path, bool ChallengeStage);

    glm::vec3 GetFormationPosition() override;
};

