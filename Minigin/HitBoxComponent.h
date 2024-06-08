#pragma once
#include <SDL_rect.h>

#include "Component.h"

namespace bew
{
	class HitBoxComponent :
		public Component
	{
	public:
		HitBoxComponent(GameObject* pparentObject, SDL_Rect hitBox);
		virtual ~HitBoxComponent() = default;

		void Render() const override;

		void SetHitBox(SDL_Rect hitbox);

		void SetDrawHitBox(bool drawHitBox) { m_DrawHitBox = drawHitBox; }
		SDL_Rect GetHitBox() const;
		SDL_Rect GetHitBoxRaw() const { return m_hitbox; }

		bool InsideHitBox(SDL_Rect OtherHitBox);
		bool InsideHitBox(GameObject* OtherObject);

		HitBoxComponent(const HitBoxComponent& other) = delete;
		HitBoxComponent(HitBoxComponent&& other) = delete;
		HitBoxComponent& operator=(const HitBoxComponent& other) = delete;
		HitBoxComponent& operator=(HitBoxComponent&& other) = delete;
	private:
		bool m_DrawHitBox{ false };
		SDL_Rect m_hitbox;
	};
}


