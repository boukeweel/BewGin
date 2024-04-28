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

		//void FixedUpdate() override;
		void Render() const override;

		void SetDrawHitBox(bool drawHitBox) { m_DrawHitBox = drawHitBox; }
		SDL_Rect GetHitBox() const;

		bool InsideHitBox(SDL_Rect OtherHitBox);

		HitBoxComponent(const HitBoxComponent& other) = delete;
		HitBoxComponent(HitBoxComponent&& other) = delete;
		HitBoxComponent& operator=(const HitBoxComponent& other) = delete;
		HitBoxComponent& operator=(HitBoxComponent&& other) = delete;

	private:
		bool m_DrawHitBox{ false };
		SDL_Rect m_hitbox;
	};
}


