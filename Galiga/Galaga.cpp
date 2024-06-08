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
#include "EnemyComponent.h"
#include "GaligaScene.h"
#include "GameData.h"
#include "HighScoreScene.h"
#include "LoggingSDLSoundSystem.h"
#include "SDLSoundSystem.h"
#include "ShotDataScene.h"
#include "SoundServiceLocator.h"
#include "StartMenuScene.h"

void AddTestingInputs()
{
	auto& input = bew::InputManager::GetInstance();

	input.AddInput(bew::ActionKeys::MoveUpKeyBoard, { {SDL_SCANCODE_W,SDL_SCANCODE_UP}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveDownKeyBoard, { {SDL_SCANCODE_S,SDL_SCANCODE_DOWN}, {}, {} });
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

	input.AddInput(bew::ActionKeys::F1, { {SDL_SCANCODE_F1}, {}, {} });
	input.AddInput(bew::ActionKeys::F2, { {SDL_SCANCODE_F2}, {}, {} });
}

void LoadInAudio()
{
#if NDEBUG
	bew::SoundServiceLocator::RegisterSoundSystem(std::make_unique<bew::SDLSoundSystem>());
#else
	bew::SoundServiceLocator::RegisterSoundSystem(std::make_unique<bew::LoggingSDLSoundSystem>(std::make_unique<bew::SDLSoundSystem>()));
#endif

	//todo load in via thread
	bew::SoundServiceLocator::GetSoundSystem().AddClip(0, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/galaga_shot.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(1, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/galaga_destroyed.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(2, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/galaga_destroyed2.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(3, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/galaga_dive.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(4, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/bossgalaga_injured.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(5, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/bossgalaga_destroyed.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(6, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/tractor_beamDown.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(7, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/tractor_beamUp.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(8, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/fighter_captured.wav")));
	bew::SoundServiceLocator::GetSoundSystem().AddClip(9, std::move(bew::ResourceManager::GetInstance().LoadAudio("Sounds/fighter_destroyed.wav")));
}

void LoadInScenes()
{
	bew::SceneManager::GetInstance().CreateScene("StartMenu", std::make_unique<StartMenuScene>());
	bew::SceneManager::GetInstance().CreateScene("Galiga", std::make_unique<GaligaScene>());
	bew::SceneManager::GetInstance().CreateScene("ShotData", std::make_unique<ShotDataScene>());
	bew::SceneManager::GetInstance().CreateScene("HighScore", std::make_unique<HighScoreScene>());
}

void load()
{
	AddTestingInputs();

	LoadInScenes();

	LoadInAudio();

	//create the paths for the enemies
	EnemyComponent::CreatePaths();
	BeeEnemyComponent::CreateAttackingPaths();
	ButterfliesEnemyComponent::CreateAttackingPaths();
	BossEnemyComponent::CreateAttackingPaths();

	GameData::GetInstance().LoadLeaderBoard();

	bew::SceneManager::GetInstance().LoadScene(0);
}

int main(int, char* []) {
	bew::BewGin engine("../Data/");
	engine.Run(load);
	return 0;
}

