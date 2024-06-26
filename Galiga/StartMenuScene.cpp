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

#include "GameData.h"
#include "SwitchLevelSceneCommands.h"

void StartMenuScene::Load()
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
		Star->AddComponent<StarComponent>(bew::ScreenWidth);
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

	auto Logo = std::make_unique<bew::GameObject>();
	Logo->SetPosition(bew::ScreenHeight / 2 + 25, 200);
	Logo->SetScale(0.5f, 0.5f);
	Logo->AddComponent<bew::TextureComponent>("Logo.png");

	scene.Add(std::move(Logo));

	auto PlayerOne = std::make_unique<bew::GameObject>();
	PlayerOne->SetPosition(225, 300);
	PlayerOne->AddComponent<bew::TextComponent>("1 PLAYER", fontTxt);

	auto PlayerTwo = std::make_unique<bew::GameObject>();
	PlayerTwo->SetPosition(225, 330);
	PlayerTwo->AddComponent<bew::TextComponent>("2 PLAYERS", fontTxt);

	auto SelectArrow = std::make_unique<bew::GameObject>();
	SelectArrow->SetPosition(200, 305);
	SelectArrow->AddComponent<bew::TextureComponent>("UiArrow.png");
	SelectArrow->AddComponent<UiArrowComponent>(30, 2);

	auto ControlsKeyBoard = std::make_unique<bew::GameObject>();
	ControlsKeyBoard->SetPosition(120, 390);
	ControlsKeyBoard->AddComponent<bew::TextComponent>("MOVE ARROW KEYS, SHOOT Z", fontTxt);

	auto ControlsController = std::make_unique<bew::GameObject>();
	ControlsController->SetPosition(160, 425);
	ControlsController->AddComponent<bew::TextComponent>("MOVE DPAD, SHOOT A", fontTxt);

	auto MuteText = std::make_unique<bew::GameObject>();
	MuteText->SetPosition(145, 475);
	MuteText->AddComponent<bew::TextComponent>("MUTE AUDIO X OR CTR X", fontTxt);

	input.AddCommand(bew::ActionKeys::DpadX, bew::ButtonState::Up, std::make_unique<MuteUnmuteCommand>(MuteText.get()));
	input.AddCommand(bew::ActionKeys::ActionKeyTwoKeyBoard, bew::ButtonState::Up, std::make_unique<MuteUnmuteCommand>(MuteText.get()));

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
	scene.Add(std::move(ControlsKeyBoard));
	scene.Add(std::move(ControlsController));
	scene.Add(std::move(MuteText));
}
