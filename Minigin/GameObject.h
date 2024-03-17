#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec3& pos);
		glm::vec3& GetWorldPosition();
		Transform GetTransform() const;

		GameObject* GetParrent() const;
		void SetParrent(GameObject* pParent, bool KeepWorldPosition = false);

		int GetChildCount() const;
		GameObject* GetChildAtIndex(int index) const;

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
			for (const auto& component : m_pComponents)
			{
				T* desiredComponent = dynamic_cast<T*>(component.get());
				if(desiredComponent != nullptr)
				{
					return desiredComponent;
				}
			}
			return nullptr;
		}
		template<typename T>
		bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}

		GameObject();
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void SetPositionDirty();
	private:
		Transform m_transform{};
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};

		std::vector<std::unique_ptr<Component>> m_pComponents{};

		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		bool m_PositionDirty{false};

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* newParent) const;

		void UpdateWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);
		
	};
}
