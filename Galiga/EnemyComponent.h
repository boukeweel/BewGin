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

    EnemyComponent(bew::GameObject* pParentObject);

    void FixedUpdate() override;
    void Update() override;
    void Render() const override;

    virtual void HandelStates();

    float GetSpeed() const { return m_speed; }
    std::vector<glm::vec2>* getPath(int index) { return &s_Paths[index]; }
    bool GetIsChallengeStage() const { return m_ChallengeStage; }
    FormationComponent* GetFormation() const { return pFormation; }
    int GetCurrentPath() const { return m_CurrentPath; }

	void SetFormationPosition(FormationComponent* formation, glm::vec3 posIndex);

    glm::vec3 GetTargetPos() const { return m_TargetPos; }

    void SetPath(int path) { m_CurrentPath = path; }
    void SetChallengeStage(bool ChallengeStage) { m_ChallengeStage = ChallengeStage; }

    

    virtual ~EnemyComponent() override;
    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) = delete;
private:
    virtual void TakeDamages(bew::GameObject* pPlayer) = 0;
protected:
    std::vector < bew::GameObject*>* GetPlayer() { return m_pPlayers; }


    void CheckInHitBox();
   

    std::vector <bew::GameObject*>* m_pPlayers;

    EnemyStates* m_States;

    float m_speed;
    glm::vec3 m_TargetPos{};
    bool m_ChallengeStage;
    int m_CurrentPath{0};

    FormationComponent* pFormation;

    //static because All enemies need them to be the same exact thing
    static std::vector<std::vector<glm::vec2>> s_Paths;
};

