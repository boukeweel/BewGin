#pragma once
#include <glm/vec2.hpp>

#include "Command.h"

namespace dae
{
	class MoveUp final : public Command
	{
	public:
		MoveUp() = default;
		void Execute(GameObject* gameobject) override;

		MoveUp(const MoveUp& other) = delete;
		MoveUp(MoveUp&& other) = delete;
		MoveUp& operator=(const MoveUp& other) = delete;
		MoveUp& operator=(MoveUp&& other) = delete;
	};

	class MoveDown final : public Command
	{
	public:
		MoveDown() = default;
		void Execute(GameObject* gameobject) override;

		MoveDown(const MoveDown& other) = delete;
		MoveDown(MoveDown&& other) = delete;
		MoveDown& operator=(const MoveDown& other) = delete;
		MoveDown& operator=(MoveDown&& other) = delete;
	};

	class MoveLeft final : public Command
	{
	public:
		MoveLeft() = default;
		void Execute(GameObject* gameobject) override;

		MoveLeft(const MoveLeft& other) = delete;
		MoveLeft(MoveLeft&& other) = delete;
		MoveLeft& operator=(const MoveLeft& other) = delete;
		MoveLeft& operator=(MoveLeft&& other) = delete;
	};

	class MoveRight final : public Command
	{
	public:
		MoveRight() = default;
		void Execute(GameObject* gameobject) override;

		MoveRight(const MoveRight& other) = delete;
		MoveRight(MoveRight&& other) = delete;
		MoveRight& operator=(const MoveRight& other) = delete;
		MoveRight& operator=(MoveRight&& other) = delete;
	};

	class ReleaseUpDown final : public Command
	{
	public:
		ReleaseUpDown() = default;
		void Execute(GameObject* gameobject) override;

		ReleaseUpDown(const ReleaseUpDown& other) = delete;
		ReleaseUpDown(ReleaseUpDown&& other) = delete;
		ReleaseUpDown& operator=(const ReleaseUpDown& other) = delete;
		ReleaseUpDown& operator=(ReleaseUpDown&& other) = delete;
	};

	class ReleaseRightLeft final : public Command
	{
	public:
		ReleaseRightLeft() = default;
		void Execute(GameObject* gameobject) override;

		ReleaseRightLeft(const ReleaseRightLeft& other) = delete;
		ReleaseRightLeft(ReleaseRightLeft&& other) = delete;
		ReleaseRightLeft& operator=(const ReleaseRightLeft& other) = delete;
		ReleaseRightLeft& operator=(ReleaseRightLeft&& other) = delete;
	};
}

