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
#include "TextObserver.h"
#include "InputManager.h"
#include "MoveCommands.h"
#include "ScoreComponent.h"
#include "TempComands.h"
#include "TextComponent.h"
#include "TextureComponent.h"

void SetControllersPlayer1(dae::InputManager& input, dae::GameObject* player)
{
	input.AddCommand("W", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand("S", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand("D", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand("A", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));

	input.AddCommand("E", dae::ButtonState::Up, std::make_unique<dae::DammagesPlayer>(player, 1));
}

void SetControllersPlayer2(dae::InputManager& input, dae::GameObject* player)
{
	input.AddCommand("DpadUP", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand("DpadDown", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand("DpadRight", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand("DpadLeft", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));

	input.AddCommand("DpadA", dae::ButtonState::Up, std::make_unique<dae::DammagesPlayer>(player, 1));
}

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.tga");
	go->SetPosition(320, 240);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.tga");
	go->SetPosition(320, 200);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto Title = std::make_unique<dae::GameObject>();
	Title->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	Title->SetPosition(80, 20);
	scene.Add(std::move(Title));

	auto fpsText = std::make_unique<dae::GameObject>();
	fpsText->AddComponent<dae::TextComponent>("fps", font);
	fpsText->AddComponent<dae::FpsComponent>();
	fpsText->SetPosition(0, 60);
	scene.Add(std::move(fpsText));

	//----------------------------------------------------------------------------

	auto fontScoreTxt = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 11);

	auto Player1 = std::make_unique<dae::GameObject>();
	Player1->AddComponent<dae::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 200);
	Player1->AddComponent<dae::HealthComponent>(3);
	Player1->AddComponent<dae::ScoreComponent>();

	auto Player1ScoreText = std::make_unique<dae::GameObject>();
	Player1ScoreText->SetPosition(0, 185);
	auto textScorep1 = Player1ScoreText->AddComponent<dae::TextComponent>("Player1 Score: ", fontScoreTxt);

	Player1->GetSubject()->AddObserver(std::make_unique<dae::TextObserver>(textScorep1));
	//this to get the first lives on screen
	//I am aware that this is not really how i should do it but I cant think of anything else atm
	Player1->GetSubject()->notify(dae::GameEvents::PlayerTookDamages, Player1.get());

	scene.Add(std::move(Player1ScoreText));

	auto Player1HealthText = std::make_unique<dae::GameObject>();
	Player1HealthText->SetPosition(0, 200);
	auto textLivesp1 = Player1HealthText->AddComponent<dae::TextComponent>("Player1 Lives: ", fontScoreTxt);

	Player1->GetSubject()->AddObserver(std::make_unique<dae::TextObserver>(textLivesp1));
	//this to get the first lives on screen
	//I am aware that this is not really how i should do it but I cant think of anything else atm
	Player1->GetSubject()->notify(dae::GameEvents::PlayerTookDamages, Player1.get());

	scene.Add(std::move(Player1HealthText));

	SetControllersPlayer1(input, Player1.get());

	//---------------------------------------------

	auto Player2 = std::make_unique<dae::GameObject>();
	Player2->AddComponent<dae::TextureComponent>("Player2.png");
	Player2->SetPosition(220, 200);
	Player2->AddComponent<dae::HealthComponent>(3);
	auto Player2ScoreText = std::make_unique<dae::GameObject>();
	Player2ScoreText->SetPosition(0, 215);
	auto textScorep2 = Player2ScoreText->AddComponent<dae::TextComponent>("Player1 Score: ", fontScoreTxt);

	Player2->GetSubject()->AddObserver(std::make_unique<dae::TextObserver>(textScorep2));
	//this to get the first lives on screen
	//I am aware that this is not really how i should do it but I cant think of anything else atm
	Player2->GetSubject()->notify(dae::GameEvents::PlayerAddedScore, Player2.get());

	scene.Add(std::move(Player2ScoreText));

	auto Player2HealthText = std::make_unique<dae::GameObject>();
	Player2HealthText->SetPosition(0, 230);

	auto textp2 = Player2HealthText->AddComponent<dae::TextComponent>("Player2 Lives: ", fontScoreTxt);

	//todo look if you could amby make this in a way that I can use 1 shared pointer instead of 2 uniqe pointers
	Player2->GetSubject()->AddObserver(std::make_unique<dae::TextObserver>(textp2));
	//this to get the first lives on screen
	//I am aware that this is not really how i should do it but I cant think of anything else atm
	Player2->GetSubject()->notify(dae::GameEvents::PlayerTookDamages, Player2.get());

	scene.Add(std::move(Player2HealthText));

	SetControllersPlayer2(input, Player2.get());

	scene.Add(std::move(Player1));
	scene.Add(std::move(Player2));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}