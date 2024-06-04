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

#include "BewGin.h"
#include "EnemyAttackControllerComponent.h"
#include "EnemyComponent.h"
#include "EnemySpawnerComponent.h"
#include "FormationComponent.h"
#include "GameData.h"
#include "GameEntityData.h"
#include "HealthComponent.h"
#include "HitBoxComponent.h"
#include "LivesDisplayObserver.h"
#include "ObjectPoolingComponent.h"
#include "PlayerComponent.h"
#include "PlayerHealthDisplayComponent.h"
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

	auto fontTxt = bew::ResourceManager::GetInstance().LoadFont("PressStart2P-Regular.ttf", 14);

	auto HighScoretxt = std::make_unique<bew::GameObject>();
	HighScoretxt->SetPosition(500, 50);
	HighScoretxt->AddComponent<bew::TextComponent>("HIGHSCORE", fontTxt,SDL_Color{255,0,0,255});

	//todo get highscore
	auto HighScoreScore = std::make_unique<bew::GameObject>();
	HighScoreScore->SetPosition(500, 70);
	HighScoreScore->AddComponent<bew::TextComponent>("30000", fontTxt);
	scene.Add(std::move(HighScoreScore));
	scene.Add(std::move(HighScoretxt));

	auto startexture = bew::ResourceManager::GetInstance().LoadTexture("Stars.png");

	for (int i = 0; i < 50; ++i)
	{
		auto testStar = std::make_unique<bew::GameObject>();
		testStar->AddComponent<bew::SpriteSheetComponent>(startexture, 1, 4);
		testStar->AddComponent<StarComponent>(bew::ScreenWidth - 150);
		scene.Add(std::move(testStar));
	}

	auto EnemyHandlerObject = std::make_unique<bew::GameObject>();
	EnemyHandlerObject->SetPosition(bew::ScreenWidth * 0.1f, 50.f);
	EnemyHandlerObject->AddComponent<FormationComponent>();
	EnemyHandlerObject->AddComponent<EnemyAttackControllerComponent>();
	auto enemiesSpawner = EnemyHandlerObject->AddComponent<EnemySpawnerComponent>();
	enemiesSpawner->AddLevel("Formation1.txt");

	//enemiesSpawner->NextLevel();

	
	auto Player1 = std::make_unique<bew::GameObject>();
	Player1->AddComponent<bew::TextureComponent>("Player1.png");
	Player1->SetPosition(bew::ScreenWidth * 0.4f, 440);
	Player1->SetScale(2, 2);
	Player1->AddComponent<ObjectPoolingComponent>(std::make_unique<BulletPreset>(), 10, glm::vec3{ 0,-10,0 });
	Player1->AddComponent<ScoreComponent>();
	auto healthP1Comp = Player1->AddComponent<HealthComponent>(3);
	Player1->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });
	Player1->AddComponent<PlayerComponent>();
	auto Player1Subject = Player1->AddComponent<bew::SubjectComponent>();

	GameEntityData::GetInstance().AddPlayer(Player1.get());

	auto Player1ScoreText = std::make_unique<bew::GameObject>();
	Player1ScoreText->SetPosition(550, 140);
	auto textScorep1 = Player1ScoreText->AddComponent<bew::TextComponent>(" ", fontTxt);

	auto Up1Text = std::make_unique<bew::GameObject>();
	Up1Text->SetPosition(560, 120);
	Up1Text->AddComponent<bew::TextComponent>("1UP", fontTxt,SDL_Color{255,0,0,255});

	auto Player1HealthDisplay = std::make_unique<bew::GameObject>();
	Player1HealthDisplay->SetPosition(520, 300);
	auto DisplayHealth = Player1HealthDisplay->AddComponent<PlayerHealthDisplayComponent>(healthP1Comp->GetLives());

	Player1Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep1));
	Player1Subject->GetSubject()->AddObserver(std::make_unique<LivesDisplayObserver>(DisplayHealth));

	

	if (GameData::GetInstance().GetTwoPlayers())
	{
		auto Player2 = std::make_unique<bew::GameObject>();
		Player2->AddComponent<bew::TextureComponent>("Player1.png");
		Player2->SetPosition(bew::ScreenWidth * 0.4f + 30, 440);
		Player2->SetScale(2, 2);
		Player2->AddComponent<ObjectPoolingComponent>(std::make_unique<BulletPreset>(), 10, glm::vec3{ 0,-10,0 });
		Player2->AddComponent<ScoreComponent>();
		auto healthP2Comp = Player2->AddComponent<HealthComponent>(3);
		Player2->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });
		Player2->AddComponent<PlayerComponent>();
		auto Player2Subject = Player2->AddComponent<bew::SubjectComponent>();

		GameEntityData::GetInstance().AddPlayer(Player1.get());

		auto Player2ScoreText = std::make_unique<bew::GameObject>();
		Player2ScoreText->SetPosition(550, 190);
		auto textScorep2 = Player2ScoreText->AddComponent<bew::TextComponent>(" ", fontTxt);

		auto Up2Text = std::make_unique<bew::GameObject>();
		Up2Text->SetPosition(560, 170);
		Up2Text->AddComponent<bew::TextComponent>("2UP", fontTxt, SDL_Color{ 255,0,0,255 });

		auto Player2HealthDisplay = std::make_unique<bew::GameObject>();
		Player2HealthDisplay->SetPosition(520, 340);
		auto DisplayP2Health = Player2HealthDisplay->AddComponent<PlayerHealthDisplayComponent>(healthP2Comp->GetLives());

		Player2Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep2));
		Player2Subject->GetSubject()->AddObserver(std::make_unique<LivesDisplayObserver>(DisplayP2Health));

		scene.Add(std::move(Player2ScoreText));
		scene.Add(std::move(Player2HealthDisplay));
		scene.Add(std::move(Player2));
		scene.Add(std::move(Up2Text));

		Player1->SetPosition(bew::ScreenWidth * 0.4f - 30, 440);
		SetControlsTwoPlayers(input, Player1.get(), Player2.get());
	}
	else
	{
		SetControlsSinglePlayer(input, Player1.get());
	}

	input.AddCommand(bew::ActionKeys::Num9, bew::ButtonState::Up, std::make_unique<NextWave>(EnemyHandlerObject.get()));

	scene.Add(std::move(EnemyHandlerObject));
	scene.Add(std::move(Player1ScoreText));
	scene.Add(std::move(Player1HealthDisplay));
	scene.Add(std::move(Player1));
	scene.Add(std::move(Up1Text));


}

void GaligaScene::SetControlsSinglePlayer(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Down, std::make_unique<ShootCommand>(player));

	input.AddCommand(bew::ActionKeys::DpadRight, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadLeft, bew::ButtonState::Held, std::make_unique<MoveCommand>(player, glm::vec3(-1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Down, std::make_unique<ShootCommand>(player));

	
}

void GaligaScene::SetControlsTwoPlayers(bew::InputManager& input, bew::GameObject* player1, bew::GameObject* player2)
{
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player1, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Held, std::make_unique<MoveCommand>(player1, glm::vec3(-1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Down, std::make_unique<ShootCommand>(player1));

	input.AddCommand(bew::ActionKeys::DpadRight, bew::ButtonState::Held, std::make_unique<MoveCommand>(player2, glm::vec3(1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadLeft, bew::ButtonState::Held, std::make_unique<MoveCommand>(player2, glm::vec3(-1, 0, 0), 100.f));
	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Down, std::make_unique<ShootCommand>(player2));
}
