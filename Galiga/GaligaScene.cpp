#include "GaligaScene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include <iostream>
#include "BulletComponent.h"
#include "MoveCommands.h"
#include <InputKeyEnum.cpp>

#include "ObjectPoolingComponent.h"
#include "ShootCommand.h"
#include "TempComands.h"

void GaligaScene::Load()
{
	auto& input = bew::InputManager::GetInstance();
	auto& scene = bew::SceneManager::GetInstance().GetCurrentScene();

	auto fontTxt = bew::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	auto SwitchSceneTxt = std::make_unique<bew::GameObject>();
	SwitchSceneTxt->SetPosition(0, 150);
	SwitchSceneTxt->AddComponent<bew::TextComponent>("Switch to Demo scene with 0 ", fontTxt);
	scene.Add(std::move(SwitchSceneTxt));

	auto Player1 = std::make_unique<bew::GameObject>();
	Player1->AddComponent<bew::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 500);
	Player1->SetScale(2, 2);

	SetControllsP1(input, Player1.get());

	Player1->AddComponent<ObjectPoolingComponent>(std::make_unique<BulletPreset>(), 5);

	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Down, std::make_unique<ShootCommand>(Player1.get()));

	scene.Add(std::move(Player1));

	input.AddCommand(bew::ActionKeys::Num0, bew::ButtonState::Up, std::make_unique<SwitchScene>(0));
}

void GaligaScene::SetControllsP1(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
}
