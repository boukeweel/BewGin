#pragma once
#include <glm/vec3.hpp>

#include "Command.h"

namespace bew
{
	class GameObject;

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* targetObject, const glm::vec3& Direction, float speed);
		void Execute() override;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

	private:
		GameObject* m_TargetObject;
		glm::vec3 m_Direction;
		float m_Speed;
	};
}

