#pragma once
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <unordered_map>

#include "Command.h"
#include "Controller.h"
#include "Singleton.h"
#include "string"




namespace dae
{
	struct CommandInfo
	{
		GameObject* targetObject;
		std::unique_ptr<Command> command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void AddCommand(std::string Key,GameObject* targetObject ,std::unique_ptr<Command> command);

	private:
		void HandelControllerInput();
		void ProccessKeyInput(SDL_KeyboardEvent& keyEvent, const std::string& prefix);
		void ProccessKeyInput(std::string key);

		std::unordered_map<std::string, CommandInfo> m_Commands;
		Controller m_Controller{};
	};

}
