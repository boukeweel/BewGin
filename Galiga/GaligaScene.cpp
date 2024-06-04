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

	auto startexture = bew::ResourceManager::GetInstance().LoadTexture("Stars.png");

	auto HighScoretxt = std::make_unique<bew::GameObject>();
	HighScoretxt->SetPosition(500, 50);
	HighScoretxt->AddComponent<bew::TextComponent>("HIGHSCORE", fontTxt,SDL_Color{255,0,0,255});

	//todo get highscore
	auto HighScoreScore = std::make_unique<bew::GameObject>();
	HighScoreScore->SetPosition(500, 70);
	HighScoreScore->AddComponent<bew::TextComponent>("30000", fontTxt);
	scene.Add(std::move(HighScoreScore));
	scene.Add(std::move(HighScoretxt));

	for (int i = 0; i < 50; ++i)
	{
		auto testStar = std::make_unique<bew::GameObject>();
		testStar->AddComponent<bew::SpriteSheetComponent>(startexture, 1, 4);
		testStar->AddComponent<StarComponent>();
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
	auto healthComp = Player1->AddComponent<HealthComponent>(3);
	Player1->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });
	Player1->AddComponent<PlayerComponent>();
	auto Player1Subject = Player1->AddComponent<bew::SubjectComponent>();

	SetControllsP1(input, Player1.get());
	GameEntityData::GetInstance().AddPlayer(Player1.get());

	auto Player1ScoreText = std::make_unique<bew::GameObject>();
	Player1ScoreText->SetPosition(550, 140);
	auto textScorep1 = Player1ScoreText->AddComponent<bew::TextComponent>(" ", fontTxt);

	auto Player1HealthDisplay = std::make_unique<bew::GameObject>();
	Player1HealthDisplay->SetPosition(520, 300);
	auto DisplayHealth = Player1HealthDisplay->AddComponent<PlayerHealthDisplayComponent>(healthComp->GetLives());

	Player1Subject->GetSubject()->AddObserver(std::make_unique<ScoreTextObserver>(textScorep1));
	Player1Subject->GetSubject()->AddObserver(std::make_unique<LivesDisplayObserver>(DisplayHealth));

	input.AddCommand(bew::ActionKeys::Num9, bew::ButtonState::Up, std::make_unique<NextWave>(EnemyHandlerObject.get()));

	scene.Add(std::move(EnemyHandlerObject));
	scene.Add(std::move(Player1ScoreText));
	scene.Add(std::move(Player1HealthDisplay));
	scene.Add(std::move(Player1));


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
