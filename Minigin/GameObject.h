#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;

	//todo should be final
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename T,typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
			std::shared_ptr<T> newComponent = std::make_shared<T>(m_transform,std::forward<Args>(args)...);
			T* rawPointer = newComponent.get();
			m_Components.push_back(std::move(newComponent));
			return rawPointer;
		}
		template<typename T>
		void RemoveComponent()
		{
			m_Components.erase(std::remove_if(std::begin(m_Components), std::end(m_Components), [](const std::unique_ptr<Component>& component)
				{
					return dynamic_cast<T*>(component.get()) != nullptr;
				}), std::end(m_Components));
		}
		template<typename T>
		T* GetComponent() const
		{
			for (const auto& component : m_Components)
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

	private:
		Transform m_transform{};

		std::vector<std::shared_ptr<Component>> m_Components;

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};
}
