#pragma once
#include "Component.h"

namespace dae
{
	class RotatorComponent final :
		public Component
	{
	public:
		RotatorComponent(GameObject* pParentObject, float radius, float RotationSpeed = 1);

		void Update(float deltaTime) override;
	private:
		float m_Radius;
		const float m_RotationSpeed;
		float m_CurrentRotation;
		glm::vec3 m_Center;
	};
}

