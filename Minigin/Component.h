#pragma once
#include "Transform.h"

namespace bew
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pparentObject);
		virtual ~Component() = default;

		virtual void FixedUpdate(){}
		virtual void Update(){}
		virtual void Render() const{}

	protected:
		GameObject* GetParentObject() const;

	private:
		GameObject* m_pParentObject;
	};
}
