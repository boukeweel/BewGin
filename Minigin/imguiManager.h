#pragma once
#include <SDL_video.h>
#include <vector>

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

class imguiManager
{
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

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



