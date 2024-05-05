#pragma once
#include <Component.h>
#include <vector>

namespace bew
{
	enum class GameEvents;
}

class EnemyComponent :
    public bew::Component
{
public:
    EnemyComponent(bew::GameObject* pParentObject, bew::GameObject* Player);

    void FixedUpdate() override;

    virtual ~EnemyComponent() = default;
    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) = delete;
private:

    void CheckInHitBox();

    bew::GameObject* m_pPlayer;
    std::vector<bew::GameObject*>* m_pBulletVector;
};

