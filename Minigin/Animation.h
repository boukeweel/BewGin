#pragma once
#include <vector>

#include "Component.h"

namespace bew
{
	class SpriteSheetComponent;

	struct KeyFrame
	{
		int row;
		int column;
	};

	//this is more a animtion class than animator
	class Animation : public Component
	{
	public:
		Animation(GameObject* pParentObject, const std::vector<KeyFrame>& keyframes, double frameDuration,bool looping);

		void Update() override;

		void SetKeyFrames(const std::vector<KeyFrame>& keyframes);
		void SetFrameDuration(double frameDuration);

		void PlayAnimation(const std::vector<KeyFrame>& keyframes, double frameDuration);
		void PlayAnimation();
		void StopAnimation();

		virtual ~Animation() = default;
		Animation(const Animation& other) = delete;
		Animation(Animation&& other) = delete;
		Animation& operator=(const Animation& other) = delete;
		Animation& operator=(Animation&& other) = delete;
	private:
		SpriteSheetComponent* m_pSpriteSheet;
		std::vector<KeyFrame> m_Keyframes{};

		double m_FrameDuration{0.0};
		int m_CurrentFrame{0};
		double m_TimeElapsed{0.0};
		bool m_IsAnimating{false};
		bool m_Looping{ true };
	};
}


