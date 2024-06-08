#pragma once
#include <memory>
#include <vector>

#include "Animation.h"
#include "Component.h"

namespace bew
{
	class AnimatorComponent : public Component
	{
	public:
		AnimatorComponent(GameObject* pParentObject);

		void Update() override;

		void SwitchAnimation(int animation,bool PlayAnimaton = false);
		void AddAnimation(std::unique_ptr<Animation> animation);

		void PlayCurrentAmation();
		void StopCurrentAnimation();

		Animation* getCurrentAnimation();

		~AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;
	private:
		std::vector<std::unique_ptr<Animation>> m_pAnimations;
		int m_CurrentAnimation;
	};
}


