#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "FormationComponent.h"
class EnemyComponent;

class EnemyStates
{
public:
	EnemyStates() = default;
	virtual ~EnemyStates() = default;

	virtual void OnEnter(EnemyComponent*){}
	virtual EnemyStates* Update(EnemyComponent*) = 0;
	virtual void Render() const {}
	virtual void OnExit(EnemyComponent*){}
};


class FlyIn final : public EnemyStates
{
public:
	FlyIn() = default;

	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void Render() const override;

private:
	int m_CurrentWayPoint{};
	int m_CurrentPath{};
	const float m_Epsilon{ 5.f };
	std::vector<glm::vec2>* m_Path{};
};

class FlyToFormationPosition final : public EnemyStates
{
public:
	FlyToFormationPosition() = default;

	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;

private:

	const float m_Epsilon{ 5.f };
};

class Formation final : public EnemyStates
{
public:
	Formation() = default;

	EnemyStates* Update(EnemyComponent* component) override;

};

class Attacking : public EnemyStates
{
public:
	Attacking() = default;
	void OnEnter(EnemyComponent* ) override{}
	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* ) override{}
	void Render() const override;

protected:
	int m_CurrentWayPoint{};
	int m_CurrentPath{};
	const float m_Epsilon{ 5.f };
	std::vector<glm::vec2>* m_Path{};
	glm::vec2 m_DiveStartPos{};
	glm::vec2 m_DiveEndPos{};
	bool m_AllowedToShoot{ false };
};


class AttackingBee final : public Attacking
{
public:
	AttackingBee() = default;
	void OnEnter(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;
};

class AttackingButterFly final : public Attacking
{
public:
	AttackingButterFly() = default;
	void OnEnter(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;
};

class AttackingBoss final : public Attacking
{
public:
	AttackingBoss() = default;
	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;

private:
	void FindEscoretButterFlies(EnemyComponent* component);

	bool m_BeamAttack{};
};

class AttackingBossBeam final : public  Attacking
{
public:
	AttackingBossBeam() = default;
	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;

private:

	bool m_Capturing{};
};
