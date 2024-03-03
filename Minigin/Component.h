#pragma once
#include "Transform.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pparentObject);
		virtual ~Component();

		virtual void Update(float deltaTime);
		virtual void Render() const{}

	protected:
		GameObject* GetParentObject() const;

	private:
		GameObject* m_pParentObject;
	};
}
