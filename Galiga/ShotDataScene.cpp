#include "ShotDataScene.h"

#include <iomanip>
#include <SDL_pixels.h>

#include "GameData.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SpriteSheetComponent.h"
#include "StarComponent.h"
#include "SwitchLevelSceneCommands.h"
#include "SwitchSceneOnTimeComponent.h"
#include "TextComponent.h"
#include <InputKeyEnum.cpp>

void ShotDataScene::Load()
{
	auto& input = bew::InputManager::GetInstance();
	auto& scene = bew::SceneManager::GetInstance().GetCurrentScene();

	input.AddCommand(bew::ActionKeys::F2, bew::ButtonState::Up, std::make_unique<NextScene>());

	auto fontTxt = bew::ResourceManager::GetInstance().LoadFont("PressStart2P-Regular.ttf", 14);

	auto startexture = bew::ResourceManager::GetInstance().LoadTexture("Stars.png");
	for (int i = 0; i < 50; ++i)
	{
		auto Star = std::make_unique<bew::GameObject>();
		Star->AddComponent<bew::SpriteSheetComponent>(startexture, 1, 4);
		Star->AddComponent<StarComponent>();
		scene.Add(std::move(Star));
	}

	auto oneUptxt = std::make_unique<bew::GameObject>();
	oneUptxt->SetPosition(50, 10);
	oneUptxt->AddComponent<bew::TextComponent>("1UP", fontTxt, SDL_Color{ 255,0,0,255 });

	auto oneUpscore = std::make_unique<bew::GameObject>();
	oneUpscore->SetPosition(100, 30);
	oneUpscore->AddComponent<bew::TextComponent>(std::to_string(GameData::GetInstance().GetCurrentScoreP1()), fontTxt);

	auto highScoretxt = std::make_unique<bew::GameObject>();
	highScoretxt->SetPosition(250, 10);
	highScoretxt->AddComponent<bew::TextComponent>("HI-SCORE", fontTxt, SDL_Color{ 255,0,0,255 });

	auto highScoreScore = std::make_unique<bew::GameObject>();
	highScoreScore->SetPosition(275, 30);
	highScoreScore->AddComponent<bew::TextComponent>(std::to_string(GameData::GetInstance().GetHighScore()), fontTxt);

	auto twoUptxt = std::make_unique<bew::GameObject>();
	twoUptxt->SetPosition(480, 10);
	twoUptxt->AddComponent<bew::TextComponent>("2UP", fontTxt, SDL_Color{ 255,0,0,255 });

	auto twoUpScore = std::make_unique<bew::GameObject>();
	twoUpScore->SetPosition(530, 30);
	twoUpScore->AddComponent<bew::TextComponent>(std::to_string(GameData::GetInstance().GetCurrentScoreP2()), fontTxt);

	auto Resulttxt = std::make_unique<bew::GameObject>();
	Resulttxt->SetPosition(230, 200);
	Resulttxt->AddComponent<bew::TextComponent>("- RESULTS -", fontTxt, SDL_Color{ 255,0,0,255 });

	auto shotsFiredtxt = std::make_unique<bew::GameObject>();
	shotsFiredtxt->SetPosition(140, 240);
	shotsFiredtxt->AddComponent<bew::TextComponent>("SHOTS FIRED ", fontTxt, SDL_Color{ 59,169,253,255 });

	auto ShotFiredScore = std::make_unique<bew::GameObject>();
	ShotFiredScore->SetPosition(400, 240);
	ShotFiredScore->AddComponent<bew::TextComponent>(std::to_string(GameData::GetInstance().GetShotsFired()), fontTxt, SDL_Color{ 59,169,253,255 });

	auto ShotHitTxt = std::make_unique<bew::GameObject>();
	ShotHitTxt->SetPosition(140, 280);
	ShotHitTxt->AddComponent<bew::TextComponent>("NUMBER OF HITS ", fontTxt);

	auto ShotHitScore = std::make_unique<bew::GameObject>();
	ShotHitScore->SetPosition(400, 280);
	ShotHitScore->AddComponent<bew::TextComponent>(std::to_string(GameData::GetInstance().GetShotsHit()),fontTxt);

	auto HitMisTxt = std::make_unique<bew::GameObject>();
	HitMisTxt->SetPosition(140, 320);
	HitMisTxt->AddComponent<bew::TextComponent>("HIT-MIS RATIO", fontTxt, SDL_Color{ 255,224,0,255 });

	auto HitMisScore = std::make_unique<bew::GameObject>();
	HitMisScore->SetPosition(400, 320);
	HitMisScore->AddComponent<bew::TextComponent>(std::to_string(GameData::GetInstance().GetHitMisRatio()) + "%", fontTxt, SDL_Color{ 255,224,0,255 });


	//timer
	auto timerObj = std::make_unique<bew::GameObject>();
	auto comp = timerObj->AddComponent<SwitchSceneOnTimeComponent>(3, 5.f);
	comp->StartTimer();
	scene.Add(std::move(timerObj));

	scene.Add(std::move(oneUptxt));
	scene.Add(std::move(oneUpscore));
	scene.Add(std::move(highScoretxt));
	scene.Add(std::move(highScoreScore));
	scene.Add(std::move(twoUptxt));
	scene.Add(std::move(twoUpScore));

	scene.Add(std::move(Resulttxt));
	scene.Add(std::move(shotsFiredtxt));
	scene.Add(std::move(ShotFiredScore));
	scene.Add(std::move(ShotHitTxt));
	scene.Add(std::move(ShotHitScore));
	scene.Add(std::move(HitMisTxt));
	scene.Add(std::move(HitMisScore));
}
