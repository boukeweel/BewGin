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
#include "TextComponent.h"
#include "TextureComponent.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto Title = std::make_shared<dae::GameObject>();
	Title->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	Title->SetPosition(80, 20);
	scene.Add(Title);

	auto fpsText = std::make_shared<dae::GameObject>();
	fpsText->AddComponent<dae::TextComponent>("fps", font);
	fpsText->AddComponent<dae::FpsComponent>();
	fpsText->SetPosition(0, 60);
	scene.Add(fpsText);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}