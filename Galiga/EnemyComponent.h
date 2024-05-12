#pragma once
#include <Component.h>
#include <vector>

#include "EnemyStates.h"


class EnemyComponent :
    public bew::Component
{
	enum class States
	{
		flyingIn,
        formation,
        attacking,
        dead
	};

public:
    static void CreatePaths();

    EnemyComponent(bew::GameObject* pParentObject, bew::GameObject* Player);

    void FixedUpdate() override;
    void Update() override;
    void Render() const override;

    virtual void HandelStates();

    float GetSpeed() const { return m_speed; }
    std::vector<glm::vec2>* getPath(int index) { return &s_Paths[index]; }

    virtual ~EnemyComponent();
    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) = delete;
protected:
    bew::GameObject* GetPlayer() { return m_pPlayer; }

private:
    void CheckInHitBox();

    bew::GameObject* m_pPlayer;
    std::vector<bew::GameObject*>* m_pBulletVector;

    EnemyStates* m_States;

    float m_speed;

    static std::vector<std::vector<glm::vec2>> s_Paths;
};

