#include "GaligaScene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include <iostream>
#include "MoveCommands.h"
#include <InputKeyEnum.cpp>

#include "AnimatorComponent.h"
#include "HitBoxComponent.h"
#include "EnemyComponent.h"
#include "HealthComponent.h"
#include "LivesTextObserver.h"
#include "ObjectPoolingComponent.h"
#include "ScoreComponent.h"
#include "ScoreTextObserver.h"
#include "ShootCommand.h"
#include "SpriteSheetComponent.h"
#include "SubjectComponent.h"
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

	auto ControlTxt = std::make_unique<bew::GameObject>();
	ControlTxt->SetPosition(0, 170);
	ControlTxt->AddComponent<bew::TextComponent>("Move with arrow Left and Right Shoot with z ", fontTxt);
	scene.Add(std::move(ControlTxt));

	auto ControlControllerTxt = std::make_unique<bew::GameObject>();
	ControlControllerTxt->SetPosition(0, 190);
	ControlControllerTxt->AddComponent<bew::TextComponent>("Move with Dpad Left and Right Shoot with DpadA ", fontTxt);
	scene.Add(std::move(ControlControllerTxt));

	

	auto Player1 = std::make_unique<bew::GameObject>();
	Player1->AddComponent<bew::TextureComponent>("Player1.png");
	Player1->SetPosition(200, 500);
	Player1->SetScale(2, 2);
	Player1->AddComponent<ObjectPoolingComponent>(std::make_unique<BulletPreset>(), 10, glm::vec3{ 0,-10,0 });
	Player1->AddComponent<ScoreComponent>();
	SetControllsP1(input, Player1.get());


	auto Enemy = std::make_unique<bew::GameObject>();
	Enemy->AddComponent<bew::TextureComponent>("EnemyBees.png");
	Enemy->AddComponent<HealthComponent>(1);
	Enemy->AddComponent<EnemyComponent>(Player1.get());
	Enemy->SetPosition(200, 100);
	Enemy->SetScale(2,2);
	Enemy->SetRotation(180);
	Enemy->AddComponent<bew::HitBoxComponent>(SDL_Rect{-8,-8,16,16})->SetDrawHitBox(true);

	auto Player1ScoreText = std::make_unique<bew::GameObject>();
	Player1ScoreText->SetPosition(0, 210);
	auto textScorep1 = Player1ScoreText->AddComponent<bew::TextComponent>("Player1 Score: ", fontTxt);

	auto Player1Subject = Player1->AddComponent<bew::SubjectComponent>();

	Player1Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep1));

	scene.Add(std::move(Player1ScoreText));
	scene.Add(std::move(Enemy));
	scene.Add(std::move(Player1));

	input.AddCommand(bew::ActionKeys::Num0, bew::ButtonState::Up, std::make_unique<SwitchScene>(0));


	auto Explotion = std::make_unique<bew::GameObject>();
	Explotion->AddComponent<bew::SpriteSheetComponent>("ExplotionSheet.png", 1, 5);
	Explotion->SetPosition(200, 400);
	std::vector<bew::KeyFrame> keyframes{ {0,0},{0, 1}, { 0, 2 }, { 0, 3 },{ 0, 4 } };
	Explotion->AddComponent<bew::AnimatorComponent>(keyframes,0.05,false)->PlayAnimation();
	

	scene.Add(std::move(Explotion));


}

void GaligaScene::SetControllsP1(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Down, std::make_unique<ShootCommand>(player));

	input.AddCommand(bew::ActionKeys::DpadRight, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadLeft, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Down, std::make_unique<ShootCommand>(player));
}
