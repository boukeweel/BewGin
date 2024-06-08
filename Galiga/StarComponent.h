#pragma once
#include "BewGin.h"
#include "Component.h"

class StarComponent : public bew::Component
{
public:
	StarComponent(bew::GameObject* pParentObject,int Width = bew::ScreenWidth);

	void Update() override;

	void ResetStar();
	void ResetPostion();
	void RandomStar();
	void ResetScale();
	void RandomSpeed();

	virtual ~StarComponent() = default;
	StarComponent(const StarComponent& other) = delete;
	StarComponent(StarComponent&& other) = delete;
	StarComponent& operator=(const StarComponent& other) = delete;
	StarComponent& operator=(StarComponent&& other) = delete;
private:
	float m_speed;
	int m_ScreenWidth;
};

