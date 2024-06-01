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

class AttackingBee final : public EnemyStates
{
public:
	AttackingBee() = default;
	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;
	void Render() const override;

private:
	int m_CurrentWayPoint{};
	int m_CurrentPath{};
	const float m_Epsilon{ 5.f };
	std::vector<glm::vec2>* m_Path{};
	glm::vec2 m_DiveStartPos;
	glm::vec2 m_DiveEndPos;
};

class AttackingButterFly final : public EnemyStates
{
public:
	AttackingButterFly() = default;
	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;
	void Render() const override;

private:
	int m_CurrentWayPoint{};
	int m_CurrentPath{};
	const float m_Epsilon{ 5.f };
	std::vector<glm::vec2>* m_Path{};
	glm::vec2 m_DiveStartPos;
	glm::vec2 m_DiveEndPos;
};

class AttackingBoss final : public EnemyStates
{
public:
	AttackingBoss() = default;
	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void OnExit(EnemyComponent* component) override;
	void Render() const override;

private:
	void FindEscoretButterFlies(EnemyComponent* component);

	int m_CurrentWayPoint{};
	int m_CurrentPath{};
	const float m_Epsilon{ 5.f };
	std::vector<glm::vec2>* m_Path{};
	glm::vec2 m_DiveStartPos;
	glm::vec2 m_DiveEndPos;
};
