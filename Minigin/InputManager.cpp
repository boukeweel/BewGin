#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"

#include <iostream>


bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN) {
			ProccessKeyInput(e.key, e.type == SDL_KEYUP ? "r_" : "p_");
			
		}
		
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}

	m_Controller.ProcessInput();
	HandelControllerInput();

	return true;
}


//idk about this way its seems rough
void dae::InputManager::AddCommand(std::string Key, GameObject* targetObject, std::unique_ptr<Command> command)
{
	m_Commands.emplace(std::move(Key), CommandInfo{ targetObject, std::move(command) });
}

void dae::InputManager::HandelControllerInput()
{
	if (m_Controller.IsDpadUpPressed())
		ProccessKeyInput("p_DpadUp");
	else if (m_Controller.IsDpadUpReleased())
		ProccessKeyInput("r_DpadUp");

	if (m_Controller.IsDpadDownPressed()) 
		ProccessKeyInput("p_DpadDown");
	else if (m_Controller.IsDpadDownReleased()) 
		ProccessKeyInput("r_DpadDown");

	if (m_Controller.IsDpadLeftPressed())
		ProccessKeyInput("p_DpadLeft");
	else if (m_Controller.IsDpadLeftReleased()) 
		ProccessKeyInput("r_DpadLeft");

	if (m_Controller.IsDpadRightPressed()) 
		ProccessKeyInput("p_DpadRight");
	else if (m_Controller.IsDpadRightReleased()) 
		ProccessKeyInput("r_DpadRight");
}

void dae::InputManager::ProccessKeyInput(SDL_KeyboardEvent& keyEvent, const std::string& prefix)
{
	std::string commandName = prefix;
	commandName.push_back(static_cast<char>(keyEvent.keysym.sym));

	ProccessKeyInput(commandName);
}

void dae::InputManager::ProccessKeyInput(const std::string& key)
{
	if (m_Commands.find(key) != m_Commands.end()) {
		CommandInfo& commandInfo = m_Commands[key];
		commandInfo.command->Execute(commandInfo.targetObject);
	}
}
