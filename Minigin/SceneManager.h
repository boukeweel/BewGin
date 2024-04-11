#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace bew
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void LoadScene(const unsigned int& idScene);
		void LoadScene(const std::string& name);

		void Update();
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		unsigned int m_CurrentScene{0};
	};
}
