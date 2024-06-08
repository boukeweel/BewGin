#pragma once
#include <Component.h>

#include "PoolComponent.h"

class BulletComponent final : public bew::Component
{
public:
    BulletComponent(bew::GameObject* pParentObject, float speed);

    void Update() override;

    void SetSpeed(float speed) { m_Speed = speed; }
    void SetDirection(glm::vec3 dir) { m_Direction = dir; }
    void SetResetHeight(float height) { m_ResetHeight = height; }

    virtual ~BulletComponent() = default;
    BulletComponent(const BulletComponent& other) = delete;
    BulletComponent(BulletComponent&& other) = delete;
    BulletComponent& operator=(const BulletComponent& other) = delete;
    BulletComponent& operator=(BulletComponent&& other) = delete;
private:
    float m_Speed;
    glm::vec3 m_Direction{ 0,-1,0 };
    float m_ResetHeight{ -10.f };
    PoolComponent* m_pPoolComp;
};

