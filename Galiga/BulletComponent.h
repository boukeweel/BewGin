#pragma once
#include <Component.h>
class BulletComponent : public bew::Component
{
public:
    BulletComponent(bew::GameObject* pParentObject, float speed);

    void Update() override;

    BulletComponent(const BulletComponent& other) = delete;
    BulletComponent(BulletComponent&& other) = delete;
    BulletComponent& operator=(const BulletComponent& other) = delete;
    BulletComponent& operator=(BulletComponent&& other) = delete;

private:
    float m_Speed;
    glm::vec3 m_Direction{ 0,-1,0 };
};

