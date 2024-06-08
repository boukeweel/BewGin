#pragma once
#include <functional>

#include "SceneManager.h"
#include "../Galiga/BaseSceneCreator.h"

namespace bew
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, std::unique_ptr<BaseSceneCreator> load);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();
		void LoadInScene();

		unsigned int GetId() { return m_id; }
		const std::string& GetName() { return m_name; }

		void ChangeActiveStateInScene(bool state);

		void FixedUpdate();
		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	private: 
		explicit Scene(const std::string& name, std::unique_ptr<BaseSceneCreator> load);

		std::unique_ptr<BaseSceneCreator> m_pLoad;

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_pObjects{};

		static unsigned int m_idCounter;
		unsigned int m_id;
	};

}
