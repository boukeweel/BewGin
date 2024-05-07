#include <stdexcept>
#include "Renderer.h"

#include "imgui.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void bew::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void bew::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_renderer);
}

void bew::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void bew::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float angle) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_Point center{};
	center.x = dst.w / 2;
	center.y = dst.h / 2;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
}

void bew::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height , const float angle) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_Point center{};
	center.x = dst.w / 2;
	center.y = dst.h / 2;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
}

void bew::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float spriteWidth, const float spriteHeight, const float srcX, const float srcY, const float srcWidth, const float srcHeight, const float angle) const
{
	SDL_Rect srcRect{ static_cast<int>(srcX), static_cast<int>(srcY), static_cast<int>(srcWidth), static_cast<int>(srcHeight) };
	SDL_Rect dstRect{ static_cast<int>(x), static_cast<int>(y), static_cast<int>(spriteWidth), static_cast<int>(spriteHeight) };

	SDL_Point center{};
	center.x = dstRect.w / 2;
	center.y = dstRect.h / 2;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, &center, SDL_FLIP_NONE);
}

void bew::Renderer::RenderRect(const SDL_Rect& rect) const
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(GetSDLRenderer(), &rect);
}

SDL_Renderer* bew::Renderer::GetSDLRenderer() const { return m_renderer; }
