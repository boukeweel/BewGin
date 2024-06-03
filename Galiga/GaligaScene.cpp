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

#include "AudioClip.h"
#include "BewGin.h"
#include "CaptureBeamComponent.h"
#include "EnemyAttackControllerComponent.h"
#include "EnemyComponent.h"
#include "FormationComponent.h"
#include "GameData.h"
#include "HitBoxComponent.h"
#include "ObjectPoolingComponent.h"
#include "ScoreComponent.h"
#include "ScoreTextObserver.h"
#include "ShootCommand.h"
#include "SpriteSheetComponent.h"
#include "StarComponent.h"
#include "SubjectComponent.h"
#include "TempComands.h"

void GaligaScene::Load()
{

	auto& input = bew::InputManager::GetInstance();
	auto& scene = bew::SceneManager::GetInstance().GetCurrentScene();

	auto fontTxt = bew::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	auto startexture = bew::ResourceManager::GetInstance().LoadTexture("Stars.png");

	for (int i = 0; i < 50; ++i)
	{
		auto testStar = std::make_unique<bew::GameObject>();
		testStar->AddComponent<bew::SpriteSheetComponent>(startexture, 1, 4);
		testStar->AddComponent<StarComponent>();
		scene.Add(std::move(testStar));
	}

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
	Player1->SetPosition(bew::ScreenWidth * 0.4f, 440);
	Player1->SetScale(2, 2);
	Player1->AddComponent<ObjectPoolingComponent>(std::make_unique<BulletPreset>(), 10, glm::vec3{ 0,-10,0 });
	Player1->AddComponent<ScoreComponent>();
	Player1->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });
	auto Player1Subject = Player1->AddComponent<bew::SubjectComponent>();

	SetControllsP1(input, Player1.get());
	GameData::GetInstance().AddPlayer(Player1.get());

	auto Player1ScoreText = std::make_unique<bew::GameObject>();
	Player1ScoreText->SetPosition(0, 210);
	auto textScorep1 = Player1ScoreText->AddComponent<bew::TextComponent>("Player1 Score: ", fontTxt);

	Player1Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep1));

	auto Formation = std::make_unique<bew::GameObject>();
	Formation->SetPosition(bew::ScreenWidth * 0.1f, 50.f);
	Formation->AddComponent<FormationComponent>("Formation1.txt");
	Formation->AddComponent<EnemyAttackControllerComponent>();

	scene.Add(std::move(Formation));
	scene.Add(std::move(Player1ScoreText));
	scene.Add(std::move(Player1));

	input.AddCommand(bew::ActionKeys::Num9, bew::ButtonState::Down, std::make_unique<AttackBoss>());
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
