#pragma once
#include "Transform.h"

namespace dae
{
	class Component
	{
	public:
		/**
		 * it will alwasys needs to transform of the Gameobject when creating it so it know with location it needs to be at
		 */
		Component(Transform& transfrom);

		virtual void Update(float deltaTime) { deltaTime += 1; }
		virtual void Render() const{}

	protected:
		Transform& m_Transform;
	};
}
