#include "BezierPath.h"

void BezierPath::AddCurve(bew::BezierCurve curve, int samples)
{
	m_Curves.emplace_back(curve);
	m_samples.emplace_back(samples);
}

void BezierPath::Sample(std::vector<glm::vec2>* samplePath)
{
	for (size_t i = 0; i < m_Curves.size(); ++i)
	{
		for (float t = 0; t <= 1.f; t += (1.f / static_cast<float>(m_samples[i])))
		{
			samplePath->emplace_back(m_Curves[i].CalculateCurvePoint(t));
		}
	}
}
