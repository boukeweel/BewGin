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
#include "InputManager.h"
#include "MoveCommands.h"
#include "PlayerMovement.h"
#include "TextComponent.h"
#include "TextureComponent.h"

void SetControllersPlayer1(dae::InputManager& input, dae::GameObject* player)
{
	input.AddCommand("p_w", player, std::make_unique<dae::MoveUp>());
	input.AddCommand("p_s", player, std::make_unique<dae::MoveDown>());
	input.AddCommand("p_d", player, std::make_unique<dae::MoveRight>());
	input.AddCommand("p_a", player, std::make_unique<dae::MoveLeft>());

	input.AddCommand("r_w", player, std::make_unique<dae::ReleaseUpDown>());
	input.AddCommand("r_s", player, std::make_unique<dae::ReleaseUpDown>());
	input.AddCommand("r_d", player, std::make_unique<dae::ReleaseRightLeft>());
	input.AddCommand("r_a", player, std::make_unique<dae::ReleaseRightLeft>());
}

void SetControllersPlayer2(dae::InputManager& input, dae::GameObject* player)
{
	input.AddCommand("p_DpadUp", player, std::make_unique<dae::MoveUp>());
	input.AddCommand("p_DpadDown", player, std::make_unique<dae::MoveDown>());
	input.AddCommand("p_DpadRight", player, std::make_unique<dae::MoveRight>());
	input.AddCommand("p_DpadLeft", player, std::make_unique<dae::MoveLeft>());

	input.AddCommand("r_DpadUp", player, std::make_unique<dae::ReleaseUpDown>());
	input.AddCommand("r_DpadDown", player, std::make_unique<dae::ReleaseUpDown>());
	input.AddCommand("r_DpadRight", player, std::make_unique<dae::ReleaseRightLeft>());
	input.AddCommand("r_DpadLeft", player, std::make_unique<dae::ReleaseRightLeft>());
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

	auto Player1 = std::make_unique<dae::GameObject>();
	Player1->AddComponent<dae::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 200);
	Player1->AddComponent<dae::PlayerMovement>(100.f);

	SetControllersPlayer1(input, Player1.get());

	auto Player2 = std::make_unique<dae::GameObject>();
	Player2->AddComponent<dae::TextureComponent>("Player2.png");
	Player2->SetPosition(220, 200);
	Player2->AddComponent<dae::PlayerMovement>(200.f);

	SetControllersPlayer2(input, Player2.get());

	scene.Add(std::move(Player1));
	scene.Add(std::move(Player2));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}