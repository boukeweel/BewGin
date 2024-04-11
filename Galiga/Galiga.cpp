#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BewGin.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "LivesTextObserver.h"
#include "MoveCommands.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ScoreTextObserver.h"
#include "SubjectComponent.h"
#include "TempComands.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include <InputKeyEnum.cpp>
#include <iostream>

void SetControllersPlayer1(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand(bew::ActionKeys::MoveUpKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveDownKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));

	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Up, std::make_unique<DammagesPlayer>(player, 1));
	input.AddCommand(bew::ActionKeys::ActionKeyTwoKeyBoard, bew::ButtonState::Up, std::make_unique<Score>(player, 100));
}

void SetControllersPlayer2(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand(bew::ActionKeys::DpadUp, bew::ButtonState::Held, 0, std::make_unique<MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadDown, bew::ButtonState::Held, 0, std::make_unique<MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadRight, bew::ButtonState::Held, 0, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadLeft, bew::ButtonState::Held, 0, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));

	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Up, std::make_unique<DammagesPlayer>(player, 1));
	input.AddCommand(bew::ActionKeys::DpadX, bew::ButtonState::Up, std::make_unique<Score>(player, 100));
}

void AddTestingInputs(bew::InputManager& input)
{
	input.AddInput(bew::ActionKeys::MoveUpKeyBoard, { {SDL_SCANCODE_W}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveDownKeyBoard, { {SDL_SCANCODE_S}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveLeftKeyBoard, { {SDL_SCANCODE_A}, {}, {} });
	input.AddInput(bew::ActionKeys::MoveRightKeyBoard, { {SDL_SCANCODE_D}, {}, {} });

	input.AddInput(bew::ActionKeys::ActionKeyOneKeyBoard, { {SDL_SCANCODE_E}, {}, {} });
	input.AddInput(bew::ActionKeys::ActionKeyTwoKeyBoard, { {SDL_SCANCODE_C}, {}, {} });

	input.AddInput(bew::ActionKeys::DpadUp, { {}, {XINPUT_GAMEPAD_DPAD_UP}, {} });
	input.AddInput(bew::ActionKeys::DpadDown, { {}, {XINPUT_GAMEPAD_DPAD_DOWN}, {} });
	input.AddInput(bew::ActionKeys::DpadLeft, { {}, {XINPUT_GAMEPAD_DPAD_LEFT}, {} });
	input.AddInput(bew::ActionKeys::DpadRight, { {}, {XINPUT_GAMEPAD_DPAD_RIGHT}, {} });

	input.AddInput(bew::ActionKeys::DpadA, { {}, {XINPUT_GAMEPAD_A}, {} });
	input.AddInput(bew::ActionKeys::DpadX, { {}, {XINPUT_GAMEPAD_X}, {} });
}

void load()
{
	auto& scene = bew::SceneManager::GetInstance().CreateScene("Galiga");
	auto& input = bew::InputManager::GetInstance();
	AddTestingInputs(input);

	auto go = std::make_unique<bew::GameObject>();
	go->AddComponent<bew::TextureComponent>("background.tga");
	go->SetPosition(320, 240);
	scene.Add(std::move(go));

	go = std::make_unique<bew::GameObject>();
	go->AddComponent<bew::TextureComponent>("logo.tga");
	go->SetPosition(320, 200);
	scene.Add(std::move(go));

	auto font = bew::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto Title = std::make_unique<bew::GameObject>();
	Title->AddComponent<bew::TextComponent>("Programming 4 Assignment", font);
	Title->SetPosition(80, 20);
	scene.Add(std::move(Title));

	auto fpsText = std::make_unique<bew::GameObject>();
	fpsText->AddComponent<bew::TextComponent>("fps", font);
	fpsText->AddComponent<bew::FpsComponent>();
	fpsText->SetPosition(0, 60);
	scene.Add(std::move(fpsText));

	auto fontTxt = bew::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	auto Player1ControlsTxt = std::make_unique<bew::GameObject>();
	Player1ControlsTxt->SetPosition(0, 100);
	Player1ControlsTxt->AddComponent<bew::TextComponent>("Move with WASD Take life with E and add score with C ", fontTxt);

	auto Player2ControlsTxt = std::make_unique<bew::GameObject>();
	Player2ControlsTxt->SetPosition(0, 120);
	Player2ControlsTxt->AddComponent<bew::TextComponent>("Move with Dpad Take life with Dpad A and add score with Dpad X ", fontTxt);

	scene.Add(std::move(Player1ControlsTxt));
	scene.Add(std::move(Player2ControlsTxt));

	//---------------------------------------------------------------------------
	auto Player1 = std::make_unique<bew::GameObject>();
	Player1->AddComponent<bew::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 200);
	Player1->AddComponent<HealthComponent>(3);
	Player1->AddComponent<ScoreComponent>();

	auto Player1ScoreText = std::make_unique<bew::GameObject>();
	Player1ScoreText->SetPosition(0, 185);
	auto textScorep1 = Player1ScoreText->AddComponent<bew::TextComponent>("Player1 Score: ", fontTxt);

	auto Player1HealthText = std::make_unique<bew::GameObject>();
	Player1HealthText->SetPosition(0, 200);
	auto textLivesp1 = Player1HealthText->AddComponent<bew::TextComponent>("Player1 Lives: ", fontTxt);

	auto Player1Subject = Player1->AddComponent<bew::SubjectComponent>();

	Player1Subject->GetSubject()->AddObserver(std::make_unique<LivesTextObserver>(textLivesp1));
	Player1Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep1));

	scene.Add(std::move(Player1HealthText));
	scene.Add(std::move(Player1ScoreText));

	SetControllersPlayer1(input, Player1.get());

	//---------------------------------------------------------------------------

	auto Player2 = std::make_unique<bew::GameObject>();
	Player2->AddComponent<bew::TextureComponent>("Player2.png");
	Player2->SetPosition(220, 200);
	Player2->AddComponent<HealthComponent>(3);
	Player2->AddComponent<ScoreComponent>();

	auto Player2ScoreText = std::make_unique<bew::GameObject>();
	Player2ScoreText->SetPosition(0, 215);
	auto textScorep2 = Player2ScoreText->AddComponent<bew::TextComponent>("Player2 Score: ", fontTxt);

	auto Player2HealthText = std::make_unique<bew::GameObject>();
	Player2HealthText->SetPosition(0, 230);
	auto textLivesp2 = Player2HealthText->AddComponent<bew::TextComponent>("Player2 Lives: ", fontTxt);

	auto Player2Subject = Player2->AddComponent<bew::SubjectComponent>();

	Player2Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep2));
	Player2Subject->GetSubject()->AddObserver(std::make_unique<LivesTextObserver>(textLivesp2));

	scene.Add(std::move(Player2ScoreText));
	scene.Add(std::move(Player2HealthText));

	SetControllersPlayer2(input, Player2.get());

	//---------------------------------------------------------------------------

	scene.Add(std::move(Player1));
	scene.Add(std::move(Player2));
}

int main(int, char* []) {
	bew::BewGin engine("../Data/");
	engine.Run(load);
	return 0;
}

