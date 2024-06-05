#include "ShotDataScene.h"

#include <iomanip>
#include <iostream>
#include <SDL_pixels.h>

#include "GameData.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SpriteSheetComponent.h"
#include "StarComponent.h"
#include "TextComponent.h"

void ShotDataScene::Load()
{
	auto& scene = bew::SceneManager::GetInstance().GetCurrentScene();

	auto fontTxt = bew::ResourceManager::GetInstance().LoadFont("PressStart2P-Regular.ttf", 14);

	auto startexture = bew::ResourceManager::GetInstance().LoadTexture("Stars.png");

	for (int i = 0; i < 50; ++i)
	{
		auto testStar = std::make_unique<bew::GameObject>();
		testStar->AddComponent<bew::SpriteSheetComponent>(startexture, 1, 4);
		testStar->AddComponent<StarComponent>();
		scene.Add(std::move(testStar));
	}

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

	scene.Add(std::move(Resulttxt));
	scene.Add(std::move(shotsFiredtxt));
	scene.Add(std::move(ShotFiredScore));
	scene.Add(std::move(ShotHitTxt));
	scene.Add(std::move(ShotHitScore));
	scene.Add(std::move(HitMisTxt));
	scene.Add(std::move(HitMisScore));
}
