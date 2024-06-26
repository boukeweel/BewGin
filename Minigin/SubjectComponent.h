#pragma once
#include "Component.h"
#include "Subject.h"

namespace bew
{
	class SubjectComponent final :
		public Component
	{
	public:
		SubjectComponent(GameObject* pParentObject) : Component(pParentObject){}

		Subject* GetSubject() const { return m_pSubject.get(); }

		virtual ~SubjectComponent() = default;
		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;
	private:
		std::unique_ptr<Subject> m_pSubject{ std::make_unique<Subject>() };
	};
}


