#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Subject.h"
#include "Transform.h"

namespace bew
{
	class Texture2D;

	class GameObject final
	{
	public:
		void FixedUpdate();
		void Update();
		void Render() const;

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec3& pos); 
		glm::vec3& GetWorldPosition();

		void SetRotation(float x);
		void SetRotation(const glm::vec3& rotation);

		void SetScale(float x, float y);
		void SetScale(const glm::vec3& scale);

		Transform GetTransform() const;

		void Translate(const glm::vec3& translation);

		GameObject* GetParrent() const;
		void SetParrent(GameObject* pParent, bool KeepWorldPosition = false);

		int GetChildCount() const;
		GameObject* GetChildAtIndex(int index) const;

		bool GetIsActive() const { return m_IsActive; }
		void SetIsActive(const bool& active) { m_IsActive = active; }

		

		template<typename T,typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
			std::unique_ptr<T> newComponent = std::make_unique<T>(this,std::forward<Args>(args)...);
			T* rawPointer = newComponent.get();
			m_pComponents.push_back(std::move(newComponent));
			return rawPointer;
		}
		template<typename T>
		void RemoveComponent()
		{
			m_pComponents.erase(std::remove_if(std::begin(m_pComponents), std::end(m_pComponents), [](const std::unique_ptr<Component>& component)
				{
					return dynamic_cast<T*>(component.get()) != nullptr;
				}), std::end(m_pComponents));
		}
		template<typename T>
		T* GetComponent() const
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return dynamic_cast<T*>(component.get()) != nullptr;
				});
			return (it != m_pComponents.end()) ? dynamic_cast<T*>(it->get()) : nullptr;
		}
		template<typename T>
		bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}

		GameObject();

		//copy operator
		GameObject(const GameObject& other) = delete;

		~GameObject() = default;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform{};
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};

		std::vector<std::unique_ptr<Component>> m_pComponents{};

		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		bool m_PositionDirty{false};

		bool m_IsActive{true};

		void SetPositionDirty();

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* newParent) const;

		void UpdateWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);
	};
}
