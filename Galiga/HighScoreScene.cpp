#include "HighScoreScene.h"

#include <iomanip>
#include <SDL_pixels.h>

#include "GameData.h"
#include "GameObject.h"
#include "InitialsComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SpriteSheetComponent.h"
#include "StarComponent.h"
#include "TextComponent.h"
#include <InputKeyEnum.cpp>
#include "LeaderBoardComponent.h"
#include "LeaderBoardObserver.h"
#include "SubjectComponent.h"
#include "SwitchLevelSceneCommands.h"
#include "SwitchSceneOnTimeComponent.h"
#include "UiCommands.h"

void HighScoreScene::Load()
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

	auto timerObj = std::make_unique<bew::GameObject>();
	auto SwitchComp = timerObj->AddComponent<SwitchSceneOnTimeComponent>(0, 5.f);

	auto oneUptxt = std::make_unique<bew::GameObject>();
	oneUptxt->SetPosition(50,10);
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

	auto LeaderBoard = std::make_unique<bew::GameObject>();
	auto leadboardcomp = LeaderBoard->AddComponent<LeaderBoardComponent>();

	//type name initials text
	auto InitialsTxtP1 = std::make_unique<bew::GameObject>();
	InitialsTxtP1->AddComponent<bew::TextComponent>("AAA", fontTxt, SDL_Color{ 255,224,0,255 });
	InitialsTxtP1->AddComponent<InitialsComponent>();
	auto subjectP1= InitialsTxtP1->AddComponent<bew::SubjectComponent>();
	subjectP1->GetSubject()->AddObserver(std::make_unique<LeaderBoardObserver>(leadboardcomp, SwitchComp));

	auto P1TxtInitails = std::make_unique <bew::GameObject>();
	P1TxtInitails->AddComponent<bew::TextComponent>("1UP", fontTxt, SDL_Color{ 255,0,0,255 });

	if(GameData::GetInstance().GetTwoPlayers())
	{
		auto InitialsTxtP2 = std::make_unique<bew::GameObject>();
		InitialsTxtP2->AddComponent<bew::TextComponent>("AAA", fontTxt, SDL_Color{ 255,224,0,255 });
		InitialsTxtP2->AddComponent<InitialsComponent>(false);
		auto subjectP2 = InitialsTxtP2->AddComponent<bew::SubjectComponent>();
		subjectP2->GetSubject()->AddObserver(std::make_unique<LeaderBoardObserver>(leadboardcomp, SwitchComp));

		InitialsTxtP2->SetPosition(380, 90);

		auto P2TxtInitails = std::make_unique <bew::GameObject>();
		P2TxtInitails->AddComponent<bew::TextComponent>("2UP", fontTxt, SDL_Color{ 255,0,0,255 });
		P2TxtInitails->SetPosition(380, 70);

		InitialsTxtP1->SetPosition(200, 90);
		P1TxtInitails->SetPosition(200, 70);
		SetControlsTwoPlayers(input, InitialsTxtP1.get(), InitialsTxtP2.get());

		scene.Add(std::move(InitialsTxtP2));
		scene.Add(std::move(P2TxtInitails));
	}
	else
	{
		InitialsTxtP1->SetPosition(285, 90);
		P1TxtInitails->SetPosition(285, 70);
		SetControlsSinglePlayer(input, InitialsTxtP1.get());
	}


	auto Top8Txt = std::make_unique<bew::GameObject>();
	Top8Txt->SetPosition(235, 120);
	Top8Txt->AddComponent<bew::TextComponent>("- BEST 8 -", fontTxt, SDL_Color{ 255,0,0,255 });

	auto NoTxt = std::make_unique<bew::GameObject>();
	NoTxt->SetPosition(170, 150);
	NoTxt->AddComponent<bew::TextComponent>("NO", fontTxt );

	auto ScoreTxt = std::make_unique<bew::GameObject>();
	ScoreTxt->SetPosition(270, 150);
	ScoreTxt->AddComponent<bew::TextComponent>("SCORE", fontTxt);

	auto IniTxt = std::make_unique<bew::GameObject>();
	IniTxt->SetPosition(400, 150);
	IniTxt->AddComponent<bew::TextComponent>("INI", fontTxt);

	auto ControllstextPart1 = std::make_unique<bew::GameObject>();
	ControllstextPart1->SetPosition(40, 440);
	ControllstextPart1->AddComponent<bew::TextComponent>("SWITCH BETWEEN LETTER DPAD OR ARROW KEYS", fontTxt);

	auto ControllstextPart2 = std::make_unique<bew::GameObject>();
	ControllstextPart2->SetPosition(50, 470);
	ControllstextPart2->AddComponent<bew::TextComponent>("SWITCH LETTER A OR Z AND FINISH X OR X", fontTxt);

	scene.Add(std::move(ControllstextPart1));
	scene.Add(std::move(ControllstextPart2));
	scene.Add(std::move(LeaderBoard));
	scene.Add(std::move(P1TxtInitails));
	scene.Add(std::move(oneUptxt));
	scene.Add(std::move(oneUpscore));
	scene.Add(std::move(highScoretxt));
	scene.Add(std::move(highScoreScore));
	scene.Add(std::move(twoUptxt));
	scene.Add(std::move(twoUpScore));
	scene.Add(std::move(Top8Txt));
	scene.Add(std::move(InitialsTxtP1));
	scene.Add(std::move(NoTxt));
	scene.Add(std::move(ScoreTxt));
	scene.Add(std::move(IniTxt));
	scene.Add(std::move(timerObj));

}

void HighScoreScene::SetControlsSinglePlayer(bew::InputManager& input, bew::GameObject* player)
{
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player, glm::vec3(1, 0, 0)));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player, glm::vec3(-1, 0, 0)));
	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Up, std::make_unique<InitialsSelecting>(player));
	input.AddCommand(bew::ActionKeys::ActionKeyTwoKeyBoard, bew::ButtonState::Up, std::make_unique<InitialFinish>(player));

	input.AddCommand(bew::ActionKeys::DpadRight, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player, glm::vec3(1, 0, 0)));
	input.AddCommand(bew::ActionKeys::DpadLeft, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player, glm::vec3(-1, 0, 0)));
	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Up, std::make_unique<InitialsSelecting>(player));
	input.AddCommand(bew::ActionKeys::DpadX, bew::ButtonState::Up, std::make_unique<InitialFinish>(player));
}

void HighScoreScene::SetControlsTwoPlayers(bew::InputManager& input, bew::GameObject* player1, bew::GameObject* player2)
{
	input.AddCommand(bew::ActionKeys::MoveRightKeyBoard, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player1, glm::vec3(1, 0, 0)));
	input.AddCommand(bew::ActionKeys::MoveLeftKeyBoard, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player1, glm::vec3(-1, 0, 0)));
	input.AddCommand(bew::ActionKeys::ActionKeyOneKeyBoard, bew::ButtonState::Up, std::make_unique<InitialsSelecting>(player1));
	input.AddCommand(bew::ActionKeys::ActionKeyTwoKeyBoard, bew::ButtonState::Up, std::make_unique<InitialFinish>(player1));

	input.AddCommand(bew::ActionKeys::DpadRight, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player2, glm::vec3(1, 0, 0)));
	input.AddCommand(bew::ActionKeys::DpadLeft, bew::ButtonState::Up, std::make_unique<InitialsMoving>(player2, glm::vec3(-1, 0, 0)));
	input.AddCommand(bew::ActionKeys::DpadA, bew::ButtonState::Up, std::make_unique<InitialsSelecting>(player2));
	input.AddCommand(bew::ActionKeys::DpadX, bew::ButtonState::Up, std::make_unique<InitialFinish>(player2));
}
