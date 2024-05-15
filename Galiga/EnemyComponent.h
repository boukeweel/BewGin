#pragma once
#include <Component.h>
#include <vector>

#include "EnemyStates.h"


class FormationComponent;


//todo clean this class up it a mess
class EnemyComponent :
    public bew::Component
{
public:
    static void CreatePaths();
    static void SetFormation(FormationComponent* formation);

    EnemyComponent(bew::GameObject* pParentObject, bew::GameObject* Player, int index, int path,bool ChallengeStage);

    void FixedUpdate() override;
    void Update() override;
    void Render() const override;

    virtual void HandelStates();

    float GetSpeed() const { return m_speed; }
    std::vector<glm::vec2>* getPath(int index) { return &s_Paths[index]; }
    bool GetIsChallengeStage() const { return m_ChallengeStage; }
    FormationComponent* GetFormation() const { return s_pFormation; }

    virtual glm::vec3 GetFormationPosition() = 0;

    glm::vec3 GetTargetPos() const { return m_TargetPos; }


    virtual ~EnemyComponent() override;
    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) = delete;
protected:
    bew::GameObject* GetPlayer() { return m_pPlayer; }

    void CheckInHitBox();

    bew::GameObject* m_pPlayer;
    std::vector<bew::GameObject*>* m_pBulletVector;

    EnemyStates* m_States;

    float m_speed;

    int m_Index;
    glm::vec3 m_TargetPos{};
    bool m_ChallengeStage;

    //static because All enemies need them to be the same exact thing
    static std::vector<std::vector<glm::vec2>> s_Paths;
    static FormationComponent* s_pFormation;
};

