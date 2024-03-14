#pragma once
#define WIN32_LEAN_AND_MEAN

#include <memory>

#include "Command.h"
#include "Singleton.h"
#include "map"
#include "string"
//#pragma comment(lib,"xinput.lib")



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

		void ProccessKeyInput(SDL_KeyboardEvent& keyEvent, const std::string& prefix);
		std::map<std::string, CommandInfo> m_Commands;
	};

}
