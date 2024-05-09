#pragma once
#include <vector>

#include "Animation.h"
#include "Component.h"

namespace bew
{
	class Animator : public Component
	{
	public:
		Animator(GameObject* pParentObject);

		void Update() override;

		void SwitchAnimation(int animation);

	private:
		std::vector<Animation> animations;
		int m_CurrentAnimation;


	};
}


