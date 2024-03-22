#pragma once
#include "Subject.h"

namespace dae
{
	class HealthComponent :
		public Subject
	{
	public:
		void TakeDammages(int amount);
		void Died();

		int GetLives() const { return m_Lifes; }

		//this is for object pooling of the enemy
		void SetLifes(int amoutLives);
		void SetBackAlive();

		HealthComponent(GameObject* pparentObject, int lives);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:
		int m_Lifes;
		bool m_IsAlive{true};
	};
}

