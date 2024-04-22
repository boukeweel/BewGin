#pragma once
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

class BaseSceneCreator;

namespace bew
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, std::unique_ptr<BaseSceneCreator> load);

		void LoadScene(unsigned int idScene);
		void LoadScene(const std::string& name);

		Scene& GetCurrentScene() const { return *m_scenes[m_CurrentScene]; }
		unsigned int GetCurrentSceneId() const { return m_CurrentScene; }

		void Update();
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		unsigned int m_CurrentScene{0};
	};
}
