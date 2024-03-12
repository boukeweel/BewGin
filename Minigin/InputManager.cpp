#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"
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
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_w:

				break;
			case SDLK_a:

				break;
			case SDLK_s:

				break;
			case SDLK_d:

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