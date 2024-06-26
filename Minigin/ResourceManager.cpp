#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"

#include <SDL_mixer.h>
#include "fstream"

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "AudioClip.h"

void bew::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<bew::Texture2D> bew::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<bew::Font> bew::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}


std::unique_ptr<bew::AudioClip> bew::ResourceManager::LoadAudio(const std::string& file) const {
	const auto fullPath = m_dataPath + file;
	Mix_Chunk* chunk = Mix_LoadWAV(fullPath.c_str());
	if (!chunk) {
		throw std::runtime_error(std::string("Failed to load audio: ") + Mix_GetError());
	}
	return std::make_unique<AudioClip>(chunk);
}

std::ifstream bew::ResourceManager::LoadTxtFileIf(const std::string& file) const
{
	std::ifstream stream{ m_dataPath + file };

	return stream;
}

std::ofstream bew::ResourceManager::LoadTxtFileOf(const std::string& file) const
{
	std::ofstream stream{ m_dataPath + file };

	return stream;
}

