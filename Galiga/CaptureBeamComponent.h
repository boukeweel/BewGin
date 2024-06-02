#pragma once
#include "Component.h"

class CaptureBeamComponent : public  bew::Component
{
public:
    CaptureBeamComponent(bew::GameObject* pParentObject);

    void Update() override;

    void ResetBeam();
    bool GetFinsihed() const { return m_Finished; }

    void StartCapturing();

    virtual ~CaptureBeamComponent() override = default;
    CaptureBeamComponent(const CaptureBeamComponent& other) = delete;
    CaptureBeamComponent(CaptureBeamComponent&& other) = delete;
    CaptureBeamComponent& operator=(const CaptureBeamComponent& other) = delete;
    CaptureBeamComponent& operator=(CaptureBeamComponent&& other) = delete;

private:
    float m_TotalBeamTime{10.f};
    float m_timer{};
    float m_SpritePart{};

    bool m_Finished;
    bool m_StartCapturing;

    bool m_Increasing{true};
    float m_SegmentTime{};
    const float m_WaitTime{1.f};
    const int m_Segments{5};
};

