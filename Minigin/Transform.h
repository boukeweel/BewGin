#pragma once
#include <glm/glm.hpp>

namespace bew
{
	//todo add rotation, position and scale
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3& pos);

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(float x, float y, float z);

		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation{0,0,0};
		glm::vec3 m_Scale{1,1,1};
	};
}
