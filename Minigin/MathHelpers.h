#pragma once
#include <glm/vec2.hpp>

namespace bew
{
	struct BezierCurve
	{
		glm::vec2 pos0;
		glm::vec2 pos1;
		glm::vec2 pos2;
		glm::vec2 pos3;

		glm::vec2 CalculateCurvePoint(float t)
		{
			float mT = 1.f - t;
			float mTSquared = mT * mT;
			float mTCubed = mTSquared * mT;

			float TSquared = t * t;
			float TCubed = TSquared * t;

			glm::vec2 point = mTCubed * pos0 + 3.f * mTSquared * t * pos1 + 3.f * mT * TSquared * pos2 + TCubed * pos3;

			return point;
		}
	};
}

