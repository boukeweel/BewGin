#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"

#include <iostream>


bool dae::InputManager::ProcessInput()
{
	HandleControllerContinually();
	HandleKeyboardContinually();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (HandelKeyBoardEvent(e)) {
			continue;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void dae::InputManager::HandleKeyboardContinually() const
{
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	for (auto&& Command : m_Commands)
	{
		for (auto&& keyboardKey : Command.m_Action.keyBoardkeys)
		{
			if (Command.m_ButtonState == ButtonState::Held && keyboardState[keyboardKey])
			{
				Command.m_Command->Execute();
				break;
			}
		}
	}
}

bool dae::InputManager::HandelKeyBoardEvent(const SDL_Event& event) const
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		const ButtonState buttonState = event.type == SDL_KEYDOWN ? ButtonState::Down : ButtonState::Up;
		for (auto&& command : m_Commands)
		{
			if (event.key.repeat)
				continue;

			command.TryExecutedKeyBoard(buttonState, event.key.keysym.scancode);
		}
		return true;
	}
	return false;
}

void dae::CommandInfo::TryExecutedKeyBoard(ButtonState checkState, SDL_Scancode key) const
{
	if (m_ButtonState != checkState)
		return;

	if (!m_Action.HasKeyboardKey(key))
		return;

	m_Command->Execute();

}

void dae::CommandInfo::TryExecutedControllerButton(ButtonState checkState, int controllerIndex, WORD button) const
{
	if (m_ButtonState != checkState)
		return;

	if (!m_Action.HasControllerButton(button))
		return;

	if (m_ControllerIndex != controllerIndex)
		return;

	m_Command->Execute();
}

void dae::CommandInfo::TryExecutedControllerAxis(int controllerIndex, DWORD axis) const
{
	if (!m_Action.HasControllerAxis(axis))
		return;

	if (m_ControllerIndex != controllerIndex)
		return;

	m_Command->Execute();

}
