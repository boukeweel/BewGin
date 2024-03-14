#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"

#include <iostream>
#include <Windows.h>
#include <Xinput.h>

#include <SDL_syswm.h>


bool dae::InputManager::ProcessInput()
{
	//for controller input
	//XINPUT_STATE state;

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_w:
				ProccessKeyInput(e.key, e.type == SDL_KEYUP ? "r_" : "p_");
				break;
			case SDLK_a:
				ProccessKeyInput(e.key, e.type == SDL_KEYUP ? "r_" : "p_");
				break;
			case SDLK_s:
				ProccessKeyInput(e.key, e.type == SDL_KEYUP ? "r_" : "p_");
				break;
			case SDLK_d:
				ProccessKeyInput(e.key, e.type == SDL_KEYUP ? "r_" : "p_");
				break;
			default:
				break;
			}
		}
		
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}

	return true;
}


//idk about this way its seems rough
void dae::InputManager::AddCommand(std::string Key, GameObject* targetObject, std::unique_ptr<Command> command)
{
	m_Commands.emplace(std::move(Key), CommandInfo{ targetObject, std::move(command) });
}

void dae::InputManager::ProccessKeyInput(SDL_KeyboardEvent& keyEvent, const std::string& prefix)
{
	std::string commandName = prefix;
	commandName.push_back(static_cast<char>(keyEvent.keysym.sym));

	if (m_Commands.find(commandName) != m_Commands.end()) {
		CommandInfo& commandInfo = m_Commands[commandName];
		commandInfo.command->Execute(commandInfo.targetObject);
	}
}
