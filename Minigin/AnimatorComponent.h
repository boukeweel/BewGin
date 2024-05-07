#pragma once
#include <vector>

#include "Component.h"

namespace bew
{
	class SpriteSheetComponent;
}

namespace bew
{
	class AnimatorComponent : public Component
	{
		struct KeyFrame
		{
			int row;
			int column;
		};
	public:
		AnimatorComponent(GameObject* pParentObject);
		AnimatorComponent(GameObject* pParentObject, const std::vector<KeyFrame>& keyframes, double frameDuration);

		void Update() override;

		void SetKeyFrames(const std::vector<KeyFrame>& keyframes);
		void SetFrameDuration(double frameDuration);

		void PlayAnimation(const std::vector<KeyFrame>& keyframes, double frameDuration);
		void PlayAnimation();
		void StopAnimation();

		virtual ~AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;
	private:
		SpriteSheetComponent* m_pSpriteSheet;
		std::vector<KeyFrame> m_Keyframes{};

		double m_FrameDuration{0.0};
		int m_CurrentFrame{0};
		double m_TimeElapsed{0.0};
		bool m_IsAnimating{false};

	};
}


