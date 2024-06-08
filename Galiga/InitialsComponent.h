#pragma once
#include <Component.h>
#include <vector>

class InitialsComponent :
    public bew::Component
{
public:
	InitialsComponent(bew::GameObject* pParentOjbect, bool Player1 = true);

	void Update() override;

	void Select();
	void MoveLeft();
	void MoveRight();
	void Finish();

	virtual ~InitialsComponent() = default;
	InitialsComponent(const InitialsComponent& other) = delete;
	InitialsComponent(InitialsComponent&& other) = delete;
	InitialsComponent& operator=(const InitialsComponent& other) = delete;
	InitialsComponent& operator=(InitialsComponent&& other) = delete;

private:
	void SetText();
	void UpdateText();

	float m_DisappearTime{ 0.2f };
	float m_VisibleTime{ 0.5f };
	float m_timer{};
	bool m_Visible{};

	char m_Initials[3];
	int m_CurrentSelected{};

	bool m_Player1{};
	bool m_AddedScore{false};
};

