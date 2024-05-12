#pragma once
#include <vector>

#include "MathHelpers.h"

class BezierPath
{
public:
	BezierPath() = default;
	~BezierPath() = default;

	void AddCurve(bew::BezierCurve curve, int samples);
	void Sample(std::vector<glm::vec2>* samplePath);

	BezierPath(const BezierPath& other) = delete;
	BezierPath(BezierPath&& other) = delete;
	BezierPath& operator=(const BezierPath& other) = delete;
	BezierPath& operator=(BezierPath&& other) = delete;
private:
	std::vector<bew::BezierCurve> m_Curves;
	std::vector<int> m_samples;
};

