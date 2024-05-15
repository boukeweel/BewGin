#pragma once
#include <Component.h>
class FormationComponent :
    public bew::Component
{
public:
    FormationComponent(bew::GameObject* pParentObject);
    
    glm::vec2 GetGridSize() const { return m_GridSize; }
    void Lock() { m_Locked = true; }

    void Update() override;

    ~FormationComponent() override = default;
    FormationComponent(const FormationComponent& other) = delete;
    FormationComponent(FormationComponent&& other) = delete;
    FormationComponent& operator=(const FormationComponent& other) = delete;
    FormationComponent& operator=(FormationComponent&& other) = delete;

private:

    float m_OffsetAmount{10.f};
    float m_OffsetTimer{0.f};
    float m_OffsetDelay{0.4f};
    int m_OffsetCounter{4};
    int m_OffsetDirection{1};

    //for breath animation
    float m_SpreadTimer{0.f};
    float m_SpreadDelay{1.f};
    int m_SpreadCounter{0};
    int m_SpreadDirection{1};

    glm::vec2 m_GridSize{16.f,32.f};

    bool m_Locked{false};
};

