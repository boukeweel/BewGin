#include "StartMenuScene.h"

#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SpriteSheetComponent.h"
#include "StarComponent.h"
#include "TextureComponent.h"
#include "UiArrowComponent.h"
#include "UiCommands.h"
#include <InputKeyEnum.cpp>

void StartMenuScene::Load()
{
	auto& input = bew::InputManager::GetInstance();
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

	auto oneUptxt = std::make_unique<bew::GameObject>();
	oneUptxt->SetPosition(50, 40);
	oneUptxt->AddComponent<bew::TextComponent>("1UP", fontTxt, SDL_Color{ 255,0,0,255 });

	//todo get previus score
	auto oneUpscore = std::make_unique<bew::GameObject>();
	oneUpscore->SetPosition(100, 70);
	oneUpscore->AddComponent<bew::TextComponent>("0", fontTxt);

	auto highScoretxt = std::make_unique<bew::GameObject>();
	highScoretxt->SetPosition(225, 40);
	highScoretxt->AddComponent<bew::TextComponent>("HI-SCORE", fontTxt, SDL_Color{ 255,0,0,255 });

	//todo get high score
	auto highScoreScore = std::make_unique<bew::GameObject>();
	highScoreScore->SetPosition(250, 70);
	highScoreScore->AddComponent<bew::TextComponent>("30000", fontTxt);

	auto twoUptxt = std::make_unique<bew::GameObject>();
	twoUptxt->SetPosition(450, 40);
	twoUptxt->AddComponent<bew::TextComponent>("2UP", fontTxt, SDL_Color{ 255,0,0,255 });

	//todo get high score
	auto twoUpScore = std::make_unique<bew::GameObject>();
	twoUpScore->SetPosition(500, 70);
	twoUpScore->AddComponent<bew::TextComponent>("0", fontTxt);

	auto Logo = std::make_unique<bew::GameObject>();
	Logo->SetPosition(bew::ScreenHeight / 2 + 25, 200);
	Logo->SetScale(0.5f, 0.5f);
	Logo->AddComponent<bew::TextureComponent>("Logo.png");

	scene.Add(std::move(Logo));

	auto PlayerOne = std::make_unique<bew::GameObject>();
	PlayerOne->SetPosition(225, 300);
	PlayerOne->AddComponent<bew::TextComponent>("1 PLAYER", fontTxt);

	//todo get high score
	auto PlayerTwo = std::make_unique<bew::GameObject>();
	PlayerTwo->SetPosition(225, 330);
	PlayerTwo->AddComponent<bew::TextComponent>("2 PLAYERS", fontTxt);

	auto SelectArrow = std::make_unique<bew::GameObject>();
	SelectArrow->SetPosition(200, 305);
	SelectArrow->AddComponent<bew::TextureComponent>("UiArrow.png");
	SelectArrow->AddComponent<UiArrowComponent>(30, 2);

	auto rights = std::make_unique<bew::GameObject>();
	rights->SetPosition(100, 390);
	rights->AddComponent<bew::TextComponent>("TM AND C 1981 1988 NAMCO LTD", fontTxt);

	auto Company = std::make_unique<bew::GameObject>();
	Company->SetPosition(160, 440);
	Company->AddComponent<bew::TextComponent>("BANDAI CO. LTD. IS", fontTxt);

	auto license = std::make_unique<bew::GameObject>();
	license->SetPosition(145, 475);
	license->AddComponent<bew::TextComponent>("LICENSED BY NINTENDO", fontTxt);

	input.AddCommand(bew::ActionKeys::MoveUpKeyBoard, bew::ButtonState::Up, std::make_unique<ArrowMove>(SelectArrow.get(), glm::vec3(0, 1, 0)));
	input.AddCommand(bew::ActionKeys::MoveDownKeyBoard, bew::ButtonState::Up, std::make_unique<ArrowMove>(SelectArrow.get(), glm::vec3(0, -1, 0)));
	input.AddCommand(bew::ActionKeys::DpadUp, bew::ButtonState::Up, std::make_unique<ArrowMove>(SelectArrow.get(), glm::vec3(0, 1, 0)));
	input.AddCommand(bew::ActionKeys::DpadDown, bew::ButtonState::Up, std::make_unique<ArrowMove>(SelectArrow.get(), glm::vec3(0, -1, 0)));
	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Up, std::make_unique<SelectOption>(SelectArrow.get()));
	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Up, std::make_unique<SelectOption>(SelectArrow.get()));

	scene.Add(std::move(oneUptxt));
	scene.Add(std::move(oneUpscore));
	scene.Add(std::move(highScoretxt));
	scene.Add(std::move(highScoreScore));
	scene.Add(std::move(twoUptxt));
	scene.Add(std::move(twoUpScore));
	scene.Add(std::move(SelectArrow));
	scene.Add(std::move(PlayerOne));
	scene.Add(std::move(PlayerTwo));
	scene.Add(std::move(rights));
	scene.Add(std::move(Company));
	scene.Add(std::move(license));
}
