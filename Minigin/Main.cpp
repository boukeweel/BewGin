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
#include "InputManager.h"
#include "MoveCommands.h"
#include "TextComponent.h"
#include "TextureComponent.h"

void SetControllersPlayer1(dae::InputManager& input, dae::GameObject* player)
{
	input.AddCommand("W", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand("S", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand("D", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand("A", dae::ButtonState::Held, std::make_unique<dae::MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
}

void SetControllersPlayer2(dae::InputManager& input, dae::GameObject* player)
{
	input.AddCommand("DpadUP", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, -1, 0), 100.f));
	input.AddCommand("DpadDown", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(0, 1, 0), 100.f));
	input.AddCommand("DpadRight", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand("DpadLeft", dae::ButtonState::Held, 0, std::make_unique<dae::MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
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

	//------------------------------------------------------------------------------------------------------

	auto Player1 = std::make_unique<dae::GameObject>();
	Player1->AddComponent<dae::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 200);
	Player1->AddComponent<dae::HealthComponent>(3);

	SetControllersPlayer1(input, Player1.get());

	//create the text component and the observer

	//------------------------------------------------------------------------------------------------------

	auto Player2 = std::make_unique<dae::GameObject>();
	Player2->AddComponent<dae::TextureComponent>("Player2.png");
	Player2->SetPosition(220, 200);

	SetControllersPlayer2(input, Player2.get());

	scene.Add(std::move(Player1));
	scene.Add(std::move(Player2));


	

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}