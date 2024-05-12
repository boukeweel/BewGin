#pragma once
#include <vector>
#include <glm/glm.hpp>
class EnemyComponent;

class EnemyStates
{
public:
	EnemyStates() = default;
	virtual ~EnemyStates() = default;

	virtual void OnEnter(EnemyComponent*){}
	virtual EnemyStates* Update(EnemyComponent*) = 0;
	virtual void Render() const{};
	virtual void OnExit(EnemyComponent*){}
};


class FlyIn final : public EnemyStates
{
public:
	FlyIn() = default;

	void OnEnter(EnemyComponent* component) override;
	EnemyStates* Update(EnemyComponent* component) override;
	void Render() const override;
	void OnExit(EnemyComponent* component) override;

private:
	int m_CurrentWayPoint{};
	int m_CurrentPath{};
	const float EPSILON{ 5.f };
	std::vector<glm::vec2>* m_Path;
};


//todo make this bozo
class Formation final : public EnemyStates
{
public:
	Formation() = default;

	EnemyStates* Update(EnemyComponent*) override { return nullptr; }
};
