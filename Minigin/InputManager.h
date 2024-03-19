#pragma once
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <SDL_syswm.h>
#include <unordered_map>
#include <Xinput.h>

#include "Command.h"
#include "Singleton.h"
#include "string"




namespace dae
{
	struct InputAction
	{
		std::vector<SDL_Scancode> keyBoardkeys;
		std::vector <WORD> ControllerButtons;

		//for stick controls
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
	};
	inline static const std::unordered_map<std::string, InputAction> INPUT_BUTTONS
	{
		{"W",{{SDL_SCANCODE_W} ,{}, {} }},
		{"S",{{SDL_SCANCODE_S} ,{}, {} }},
		{"A",{{SDL_SCANCODE_A} ,{}, {} }},
		{"D",{{SDL_SCANCODE_D} ,{}, {} }},


		{"DpadUP",		{{} ,{XINPUT_GAMEPAD_DPAD_UP}   , {} }},
		{"DpadDown",	{{} ,{XINPUT_GAMEPAD_DPAD_DOWN} , {} }},
		{"DpadLeft",	{{} ,{XINPUT_GAMEPAD_DPAD_LEFT} , {} }},
		{"DpadRight",	{{} ,{XINPUT_GAMEPAD_DPAD_RIGHT}, {} }}
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
		bool ProcessInput();

		void AddCommand(std::string Key, ButtonState state, int conrollerIndex, std::unique_ptr<Command> command)
		{
			m_Commands.emplace_back(state, conrollerIndex, INPUT_BUTTONS.at(Key), std::move(command));
		}
		void AddCommand(std::string Key, ButtonState state, std::unique_ptr<Command> command)
		{
			m_Commands.emplace_back(state, 0, INPUT_BUTTONS.at(Key), std::move(command));
		}

	private:
		bool HandelKeyBoardEvent(const SDL_Event& event) const;
		void HandleKeyboardContinually() const;

		std::vector<CommandInfo> m_Commands;
	};

}
