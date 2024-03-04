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
#include "RotatorComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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
	Player1->AddComponent<dae::RotatorComponent>(10.f,10.f);

	auto Player2 = std::make_unique<dae::GameObject>();
	Player2->AddComponent<dae::TextureComponent>("Player2.png");
	Player2->SetPosition(0, 0);
	Player2->SetParrent(Player1.get());
	Player2->AddComponent<dae::RotatorComponent>(30.f);

	scene.Add(std::move(Player1));
	scene.Add(std::move(Player2));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}