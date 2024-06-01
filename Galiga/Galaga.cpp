#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BewGin.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include <InputKeyEnum.cpp>

#include "BeeEnemyComponent.h"
#include "BossEnemyComponent.h"
#include "ButterfliesEnemyComponent.h"
#include "DemoScene.h"
#include "EnemyComponent.h"
#include "GaligaScene.h"
#include "LoggingSDLSoundSystem.h"
#include "SDLSoundSystem.h"
#include "SoundServiceLocator.h"


void AddTestingInputs()
{
	auto& input = bew::InputManager::GetInstance();

	input.AddInput(bew::ActionKeys::MoveUpKeyBoard, { {SDL_SCANCODE_W}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveDownKeyBoard, { {SDL_SCANCODE_S}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveLeftKeyBoard, { {SDL_SCANCODE_A,SDL_SCANCODE_LEFT}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveRightKeyBoard, { {SDL_SCANCODE_D, SDL_SCANCODE_RIGHT}, {}, {} });

	input.AddInput(bew::ActionKeys::ActionKeyOneKeyBoard, { {SDL_SCANCODE_Z}, {}, {} });
	input.AddInput(bew::ActionKeys::ActionKeyTwoKeyBoard, { {SDL_SCANCODE_X}, {}, {} });

	input.AddInput(bew::ActionKeys::DpadUp, { {}, {XINPUT_GAMEPAD_DPAD_UP}, {} });
	input.AddInput(bew::ActionKeys::DpadDown, { {}, {XINPUT_GAMEPAD_DPAD_DOWN}, {} });
	input.AddInput(bew::ActionKeys::DpadLeft, { {}, {XINPUT_GAMEPAD_DPAD_LEFT}, {} });
	input.AddInput(bew::ActionKeys::DpadRight, { {}, {XINPUT_GAMEPAD_DPAD_RIGHT}, {} });

	input.AddInput(bew::ActionKeys::DpadA, { {}, {XINPUT_GAMEPAD_A}, {} });
	input.AddInput(bew::ActionKeys::DpadX, { {}, {XINPUT_GAMEPAD_X}, {} });

	input.AddInput(bew::ActionKeys::Num0, { {SDL_SCANCODE_0}, {}, {} });
	input.AddInput(bew::ActionKeys::Num1, { {SDL_SCANCODE_1}, {}, {} });
	input.AddInput(bew::ActionKeys::Num9, { {SDL_SCANCODE_9}, {}, {} });
}

void load()
{
	AddTestingInputs();

	bew::SceneManager::GetInstance().CreateScene("Demo", std::make_unique<DemoScene>());
	bew::SceneManager::GetInstance().CreateScene("Galiga", std::make_unique<GaligaScene>());

	

#if NDEBUG
	bew::SoundServiceLocator::RegisterSoundSystem(std::make_unique<bew::SDLSoundSystem>());
#else
	bew::SoundServiceLocator::RegisterSoundSystem(std::make_unique<bew::LoggingSDLSoundSystem>(std::make_unique<bew::SDLSoundSystem>()));
#endif

	bew::SoundServiceLocator::GetSoundSystem().AddClip(0, std::move(bew::ResourceManager::GetInstance().LoadAudio("galaga_shot.wav")));

	//create the paths for the enemies
	EnemyComponent::CreatePaths();
	BeeEnemyComponent::CreateAttackingPaths();
	ButterfliesEnemyComponent::CreateAttackingPaths();
	BossEnemyComponent::CreateAttackingPaths();

	bew::SceneManager::GetInstance().LoadScene(1);
}

int main(int, char* []) {
	bew::BewGin engine("../Data/");
	engine.Run(load);
	return 0;
}

