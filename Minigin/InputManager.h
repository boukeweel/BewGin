#pragma once
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <SDL_syswm.h>
#include <unordered_map>
#include <Xinput.h>

#include "Command.h"
#include "Singleton.h"
#include "string"
#include <SDL_events.h>

namespace bew
{
	enum class ActionKeys;

	//todo rewrite this its to mutch form julian
	struct InputAction
	{
		std::vector<SDL_Scancode> keyBoardkeys;
		std::vector <WORD> ControllerButtons;

		//for stick controls not inplement yet, and not sure if need for galica 
		std::vector <DWORD> ControllerAxis;

		bool HasKeyboardKey(SDL_Scancode compareKey) const
		{
			return std::find(std::begin(keyBoardkeys), std::end(keyBoardkeys), compareKey) != std::end(keyBoardkeys);
		}
		bool HasControllerButton(WORD compareButton) const
		{
			return std::find(ControllerButtons.begin(), ControllerButtons.end(), compareButton) != ControllerButtons.end();
		}

		bool HasControllerAxis(DWORD compareAxis) const
		{
			return std::find(ControllerAxis.begin(), ControllerAxis.end(), compareAxis) != ControllerAxis.end();
		}

		bool operator==(const InputAction& other) const {

			//first check if the size is the same if not its not the same inputaction
			if(keyBoardkeys.size() != other.keyBoardkeys.size()
				|| ControllerButtons.size() != other.ControllerButtons.size()
				|| ControllerAxis.size() != other.ControllerAxis.size())
			{
				return false;
			}

			//makes early exit if one of the things is already mis matched
			if(!keyBoardkeys.empty())
			{
				for (size_t i = 0; i < keyBoardkeys.size(); ++i) {
					if (keyBoardkeys[i] != other.keyBoardkeys[i]) {
						return false;
					}
				}
			}
			if (!ControllerButtons.empty())
			{
				for (size_t i = 0; i < ControllerButtons.size(); ++i) {
					if (ControllerButtons[i] != other.ControllerButtons[i]) {
						return false;
					}
				}
			}
			if (!ControllerAxis.empty())
			{
				for (size_t i = 0; i < ControllerAxis.size(); ++i) {
					if (ControllerAxis[i] != other.ControllerAxis[i]) {
						return false;
					}
				}
			}

			return true;
		}
	};
	enum class ButtonState
	{
		Up,
		Down,
		Held
	};

	struct CommandInfo
	{
		ButtonState m_ButtonState;
		int m_ControllerIndex;
		InputAction m_Action;
		std::unique_ptr<Command> m_Command;

		void TryExecutedKeyBoard(ButtonState checkState, SDL_Scancode key) const;
		void TryExecutedControllerButton(ButtonState checkState, int controllerIndex, WORD button) const;
		void TryExecutedControllerAxis(int controllerIndex, DWORD axis) const;
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:

		InputManager();
		~InputManager();

		bool ProcessInput();

		void AddCommand(const ActionKeys& Key, ButtonState state, int conrollerIndex, std::unique_ptr<Command> command)
		{
			m_Commands.emplace_back(state, conrollerIndex, InputButtons.at(Key), std::move(command));
		}
		void AddCommand(const ActionKeys& Key, ButtonState state, std::unique_ptr<Command> command)
		{
			AddCommand(Key, state, 0, std::move(command));
		}

		void RemoveCommand(const ActionKeys& key) {
			m_Commands.erase(std::remove_if(m_Commands.begin(), m_Commands.end(),
				[this,&key](const CommandInfo& cmd) { return cmd.m_Action == InputButtons.at(key); }),
				m_Commands.end());
		}

		void AddInput(const ActionKeys& key, const InputAction& actions)
		{
			InputButtons[key] = actions;
		}
		void RemoveInput(const ActionKeys& key)
		{
			InputButtons.erase(key);
		}

		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_ControllerImpl;

		bool HandelKeyBoardEvent(const SDL_Event& event) const;
		void HandleKeyboardContinually() const;
		void HandleControllerContinually();
	private:
		std::unordered_map<ActionKeys, InputAction> InputButtons{};
		std::vector<CommandInfo> m_Commands;
	};

}
