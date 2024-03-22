#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

	class DammagesPlayer final : public Command
	{
	public:
		DammagesPlayer(GameObject* targetObject, int Dammages);
		void Execute() override;

		DammagesPlayer(const DammagesPlayer& other) = delete;
		DammagesPlayer(DammagesPlayer&& other) = delete;
		DammagesPlayer& operator=(const DammagesPlayer& other) = delete;
		DammagesPlayer& operator=(DammagesPlayer&& other) = delete;

	private:
		GameObject* m_TargetObject;
		int m_Damages;
	};
}



