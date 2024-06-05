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

		bool GetNeedSceneSwitch() const { return m_NeedSwitch; }
		void SwitchScene(int scene)
		{
			m_DiserdScene = scene;
			m_NeedSwitch = true;
		}
		void ExecuteSceneSwitch()
		{
			LoadScene(m_DiserdScene);
			m_NeedSwitch = false;
		}

		Scene& GetCurrentScene() const { return *m_scenes[m_CurrentScene]; }
		unsigned int GetCurrentSceneId() const { return m_CurrentScene; }

		void FixedUpdate();
		void Update();
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		unsigned int m_CurrentScene{0};

		//sceneSwitchThings
		bool m_NeedSwitch{ false };
		int m_DiserdScene{ 0 };
	};
}
