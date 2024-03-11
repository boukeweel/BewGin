#pragma once
#include <SDL_video.h>
#include <vector>

#include "Component.h"

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform;
	int ID;
};

class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

namespace dae
{
	class ImGuiTrashTheCacheComponent : public Component
	{
	public:
		ImGuiTrashTheCacheComponent(GameObject* pParentObject);

		void Render() const override;

		ImGuiTrashTheCacheComponent(const ImGuiTrashTheCacheComponent& other) = delete;
		ImGuiTrashTheCacheComponent(ImGuiTrashTheCacheComponent&& other) = delete;
		ImGuiTrashTheCacheComponent& operator=(const ImGuiTrashTheCacheComponent& other) = delete;
		ImGuiTrashTheCacheComponent& operator=(ImGuiTrashTheCacheComponent&& other) = delete;

	private:
		void GraphsExOne() const;
		void GraphsExTwo() const;

		std::vector<float> MeasureExOne(int samples) const;
		std::vector<float> MeasureExTwo(int samples) const;
		std::vector<float> MeasureExTwoAlt(int samples) const;
		void CleanUpMeasurements(std::vector<float>& durations) const;

		mutable std::vector<float> m_DurationsExOne;
		mutable std::vector<float> m_DurationsExTwo;
		mutable std::vector<float> m_DurationsExTwoAlt;
	};
}




