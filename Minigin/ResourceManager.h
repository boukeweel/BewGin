#pragma once
#include <string>
#include <memory>

#include "Singleton.h"

namespace bew
{
	class AudioClip;
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		[[nodiscard]] std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		[[nodiscard]] std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		[[nodiscard]] std::unique_ptr<AudioClip> LoadAudio(const std::string& file) const;

		[[nodiscard]] std::ifstream LoadTxtFileIf(const std::string& file) const;
		[[nodiscard]] std::ofstream LoadTxtFileOf(const std::string& file) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
