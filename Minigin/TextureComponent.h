#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* pParentObject, const std::string& filename);

		void Render() const override;

		void SetTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture();

		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other)  = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}


