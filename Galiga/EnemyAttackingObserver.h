#pragma once
#include <Observer.h>

#include "EnemyAttackControllerComponent.h"

class EnemyAttackingObserver :
	public bew::Observer
{
public:
	EnemyAttackingObserver(EnemyAttackControllerComponent* pAttackingController);

	void Notify(bew::GameEvents event, bew::GameObject*) override;

	virtual ~EnemyAttackingObserver() = default;
	EnemyAttackingObserver(const EnemyAttackingObserver& other) = delete;
	EnemyAttackingObserver(EnemyAttackingObserver&& other) = delete;
	EnemyAttackingObserver& operator=(const EnemyAttackingObserver& other) = delete;
	EnemyAttackingObserver& operator=(EnemyAttackingObserver&& other) = delete;

private:
	EnemyAttackControllerComponent* m_pAttackingController;
};

