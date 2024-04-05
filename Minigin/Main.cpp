#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FpsComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "LivesTextObserver.h"
#include "InputManager.h"
#include "MoveCommands.h"
#include "ScoreComponent.h"
#include "ScoreTextObserver.h"
#include "TempComands.h"
#include "TextComponent.h"
#include "TextureComponent.h"

void SetControllersPlayer1(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand("W", bew::ButtonState::Held, std::make_unique<bew::MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand("S", bew::ButtonState::Held, std::make_unique<bew::MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand("D", bew::ButtonState::Held, std::make_unique<bew::MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand("A", bew::ButtonState::Held, std::make_unique<bew::MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));

	input.AddCommand("E", bew::ButtonState::Up, std::make_unique<bew::DammagesPlayer>(player, 1));
	input.AddCommand("C", bew::ButtonState::Up, std::make_unique<bew::Score>(player, 100));
}

void SetControllersPlayer2(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand("DpadUP", bew::ButtonState::Held, 0, std::make_unique<bew::MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand("DpadDown", bew::ButtonState::Held, 0, std::make_unique<bew::MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand("DpadRight", bew::ButtonState::Held, 0, std::make_unique<bew::MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand("DpadLeft", bew::ButtonState::Held, 0, std::make_unique<bew::MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));

	input.AddCommand("DpadA", bew::ButtonState::Up, std::make_unique<bew::DammagesPlayer>(player, 1));
	input.AddCommand("DpadX", bew::ButtonState::Up, std::make_unique<bew::Score>(player, 100));
}

void AddTestingInputs(bew::InputManager& input)
{
	input.AddInput("W", { {SDL_SCANCODE_W}, {}, {} });
	input.AddInput("S", { {SDL_SCANCODE_S}, {}, {} });
	input.AddInput("A", { {SDL_SCANCODE_A}, {}, {} });
	input.AddInput("D", { {SDL_SCANCODE_D}, {}, {} });

	input.AddInput("E", { {SDL_SCANCODE_E}, {}, {} });
	input.AddInput("C", { {SDL_SCANCODE_C}, {}, {} });

	input.AddInput("DpadUP", { {}, {XINPUT_GAMEPAD_DPAD_UP}, {} });
	input.AddInput("DpadDown", { {}, {XINPUT_GAMEPAD_DPAD_DOWN}, {} });
	input.AddInput("DpadLeft", { {}, {XINPUT_GAMEPAD_DPAD_LEFT}, {} });
	input.AddInput("DpadRight", { {}, {XINPUT_GAMEPAD_DPAD_RIGHT}, {} });

	input.AddInput("DpadA", { {}, {XINPUT_GAMEPAD_A}, {} });
	input.AddInput("DpadX", { {}, {XINPUT_GAMEPAD_X}, {} });
}

void load()
{
	

	auto& scene = bew::SceneManager::GetInstance().CreateScene("Demo");
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

	//----------------------------------------------------------------------------

	

	auto Player1 = std::make_unique<bew::GameObject>();
	Player1->AddComponent<bew::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 200);
	Player1->AddComponent<bew::HealthComponent>(3);
	Player1->AddComponent<bew::ScoreComponent>();

	auto Player1ScoreText = std::make_unique<bew::GameObject>();
	Player1ScoreText->SetPosition(0, 185);
	auto textScorep1 = Player1ScoreText->AddComponent<bew::TextComponent>("Player1 Score: ", fontTxt);

	auto Player1HealthText = std::make_unique<bew::GameObject>();
	Player1HealthText->SetPosition(0, 200);
	auto textLivesp1 = Player1HealthText->AddComponent<bew::TextComponent>("Player1 Lives: ", fontTxt);

	Player1->GetSubject()->AddObserver(std::make_unique<bew::LivesTextObserver>(textLivesp1));
	Player1->GetSubject()->AddObserver(std::make_unique<bew::ScoreTextObserver>(textScorep1));
	
	//this to get the first lives and score on screen
	//I am aware that this is not really how i should do it but I cant think of anything else atm
	Player1->GetSubject()->notify(bew::GameEvents::PlayerTookDamages, Player1.get());
	Player1->GetSubject()->notify(bew::GameEvents::PlayerAddedScore , Player1.get());

	scene.Add(std::move(Player1HealthText));
	scene.Add(std::move(Player1ScoreText));

	SetControllersPlayer1(input, Player1.get());

	//---------------------------------------------------------------------------

	auto Player2 = std::make_unique<bew::GameObject>();
	Player2->AddComponent<bew::TextureComponent>("Player2.png");
	Player2->SetPosition(220, 200);
	Player2->AddComponent<bew::HealthComponent>(3);
	Player2->AddComponent<bew::ScoreComponent>();

	auto Player2ScoreText = std::make_unique<bew::GameObject>();
	Player2ScoreText->SetPosition(0, 215);
	auto textScorep2 = Player2ScoreText->AddComponent<bew::TextComponent>("Player2 Score: ", fontTxt);

	auto Player2HealthText = std::make_unique<bew::GameObject>();
	Player2HealthText->SetPosition(0, 230);
	auto textLivesp2 = Player2HealthText->AddComponent<bew::TextComponent>("Player2 Lives: ", fontTxt);

	Player2->GetSubject()->AddObserver(std::make_unique<bew::ScoreTextObserver>(textScorep2));
	Player2->GetSubject()->AddObserver(std::make_unique<bew::LivesTextObserver>(textLivesp2));

	//this to get the first lives and score on screen
	//I am aware that this is not really how i should do it but I cant think of anything else atm
	Player2->GetSubject()->notify(bew::GameEvents::PlayerAddedScore, Player2.get());
	Player2->GetSubject()->notify(bew::GameEvents::PlayerTookDamages, Player2.get());

	scene.Add(std::move(Player2ScoreText));
	scene.Add(std::move(Player2HealthText));

	SetControllersPlayer2(input, Player2.get());

	scene.Add(std::move(Player1));
	scene.Add(std::move(Player2));
}

int main(int, char*[]) {
	bew::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}