#pragma once
#include "Component.h"

namespace dae
{
	class PlayerMovement :
		public Component
	{
	public:
		PlayerMovement(GameObject* pParentObject,float speed);

		void Update(float deltaTime) override;

		void MoveUp();
		void MoveDown();
		void MoveRight();
		void MoveLeft();
		void ReleaseUpDown();
		void ReleaseLeftRight();

		void SetSpeed(float speed);

		virtual ~PlayerMovement() = default;
		PlayerMovement(const PlayerMovement& other) = delete;
		PlayerMovement(PlayerMovement&& other) = delete;
		PlayerMovement& operator=(const PlayerMovement& other) = delete;
		PlayerMovement& operator=(PlayerMovement&& other) = delete;

	private:
		float m_speed;
		glm::vec2 m_MoveDirection;
	};
}


