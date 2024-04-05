#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace bew
{
	class ScoreTextObserver :
		public Observer
	{
	public:
		ScoreTextObserver(TextComponent* pTextComponent);

		void Notify(GameEvents event, GameObject* gameObject) override;

		virtual ~ScoreTextObserver() = default;
		ScoreTextObserver(const ScoreTextObserver& other) = delete;
		ScoreTextObserver(ScoreTextObserver&& other) = delete;
		ScoreTextObserver& operator=(const ScoreTextObserver& other) = delete;
		ScoreTextObserver& operator=(ScoreTextObserver&& other) = delete;

	private:
		TextComponent* m_TextComponent;
		std::string m_ScoreTxt;
	};
}


