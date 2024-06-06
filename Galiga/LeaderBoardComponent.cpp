#include "LeaderBoardComponent.h"

#include "GameData.h"
#include "HighScoreEntryComponent.h"
#include "Scene.h"
#include "SceneManager.h"

LeaderBoardComponent::LeaderBoardComponent(bew::GameObject* pParentOjbect) : Component(pParentOjbect)
{
	//initial Creation
	auto HighScores = GameData::GetInstance().GetHighScoreList();
	float addedToY = 0;
	for (const auto& highScoreData : *HighScores)
	{
		auto ScoreText = std::make_unique<bew::GameObject>();
		ScoreText->SetPosition(150, 180 + addedToY);
		addedToY += 30;
		auto comp = ScoreText->AddComponent<HighScoreEntryComponent>();
		comp->CreateTextObjects(highScoreData->number, highScoreData->Score, highScoreData->Initials);
		m_Enteries.emplace_back(ScoreText.get());
		bew::SceneManager::GetInstance().AddToCurrentScene(std::move(ScoreText));
	}
}

void LeaderBoardComponent::UpdateLeaderBoared()
{
	auto HighScores = GameData::GetInstance().GetHighScoreList();
	for (size_t i = 0; i < HighScores->size() - 1; ++i)
	{
		auto comp = m_Enteries[i]->GetComponent<HighScoreEntryComponent>();
		comp->ChanceEnteryValues(HighScores->at(i)->number, HighScores->at(i)->Score, HighScores->at(i)->Initials);
	}
}
