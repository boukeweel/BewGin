#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BewGin.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommands.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TempComands.h"
#include "TextComponent.h"
#include <InputKeyEnum.cpp>
#include <iostream>
#include "DemoScene.h"
#include "GaligaScene.h"


void AddTestingInputs()
{
	auto& input = bew::InputManager::GetInstance();

	input.AddInput(bew::ActionKeys::MoveUpKeyBoard, { {SDL_SCANCODE_W}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveDownKeyBoard, { {SDL_SCANCODE_S}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveLeftKeyBoard, { {SDL_SCANCODE_A,SDL_SCANCODE_LEFT}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveRightKeyBoard, { {SDL_SCANCODE_D, SDL_SCANCODE_RIGHT}, {}, {} });

	input.AddInput(bew::ActionKeys::ActionKeyOneKeyBoard, { {SDL_SCANCODE_E}, {}, {} });
	input.AddInput(bew::ActionKeys::ActionKeyTwoKeyBoard, { {SDL_SCANCODE_C}, {}, {} });

	input.AddInput(bew::ActionKeys::DpadUp, { {}, {XINPUT_GAMEPAD_DPAD_UP}, {} });
	input.AddInput(bew::ActionKeys::DpadDown, { {}, {XINPUT_GAMEPAD_DPAD_DOWN}, {} });
	input.AddInput(bew::ActionKeys::DpadLeft, { {}, {XINPUT_GAMEPAD_DPAD_LEFT}, {} });
	input.AddInput(bew::ActionKeys::DpadRight, { {}, {XINPUT_GAMEPAD_DPAD_RIGHT}, {} });

	input.AddInput(bew::ActionKeys::DpadA, { {}, {XINPUT_GAMEPAD_A}, {} });
	input.AddInput(bew::ActionKeys::DpadX, { {}, {XINPUT_GAMEPAD_X}, {} });

	input.AddInput(bew::ActionKeys::Num0, { {SDL_SCANCODE_0}, {}, {} });
	input.AddInput(bew::ActionKeys::Num1, { {SDL_SCANCODE_1}, {}, {} });
}

void load()
{
	
	AddTestingInputs();

	bew::SceneManager::GetInstance().CreateScene("Demo", std::make_unique<DemoScene>());
	bew::SceneManager::GetInstance().CreateScene("Galiga", std::make_unique<GaligaScene>());

	bew::SceneManager::GetInstance().LoadScene(1);

	auto& input = bew::InputManager::GetInstance();

	input.AddCommand(bew::ActionKeys::Num0, bew::ButtonState::Up, std::make_unique<SwitchScene>(0));
	input.AddCommand(bew::ActionKeys::Num1, bew::ButtonState::Up, std::make_unique<SwitchScene>(1));
}

int main(int, char* []) {
	bew::BewGin engine("../Data/");
	engine.Run(load);
	return 0;
}

