#pragma once
#include <Component.h>
class SwitchSceneOnTimeComponent :
    public bew::Component
{
public:
	SwitchSceneOnTimeComponent(bew::GameObject* pParentOjbect,int Scene);
	SwitchSceneOnTimeComponent(bew::GameObject* pParentOjbect, int Scene, float Time);

	void Update() override;

	void StartTimer() { m_Start = true; }

	void StartTwoPlayers();

	virtual ~SwitchSceneOnTimeComponent() = default;
	SwitchSceneOnTimeComponent(const SwitchSceneOnTimeComponent& other) = delete;
	SwitchSceneOnTimeComponent(SwitchSceneOnTimeComponent&& other) = delete;
	SwitchSceneOnTimeComponent& operator=(const SwitchSceneOnTimeComponent& other) = delete;
	SwitchSceneOnTimeComponent& operator=(SwitchSceneOnTimeComponent&& other) = delete;
private:
	float m_TimeActive{ 10.f };
	float m_Timer;
	int m_TargetScene;

	bool m_Start{ false };
	int m_AmountCalled{ 0 };
};

