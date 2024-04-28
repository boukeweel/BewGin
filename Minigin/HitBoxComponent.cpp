
#include <SDL_render.h>

#include "GameObject.h"
#include "Renderer.h"
#include "HitBoxComponent.h"


bew::HitBoxComponent::HitBoxComponent(GameObject* pparentObject, SDL_Rect hitBox) : Component(pparentObject),m_hitbox{hitBox}
{
	m_hitbox.x *= static_cast<int>(GetParentObject()->GetTransform().GetScale().x);
	m_hitbox.y *= static_cast<int>(GetParentObject()->GetTransform().GetScale().y);
	m_hitbox.h *= static_cast<int>(GetParentObject()->GetTransform().GetScale().y);
	m_hitbox.w *= static_cast<int>(GetParentObject()->GetTransform().GetScale().x);
}

void bew::HitBoxComponent::Render() const
{
	if(m_DrawHitBox)
	{
		
		
		Renderer::GetInstance().RenderRect(GetHitBox());
	}
}

SDL_Rect bew::HitBoxComponent::GetHitBox() const
{
	SDL_Rect hitbox{ m_hitbox };
	glm::vec3 pos = GetParentObject()->GetWorldPosition();
	hitbox.x += static_cast<int>(pos.x);
	hitbox.y += static_cast<int>(pos.y);
	return hitbox;
}

bool bew::HitBoxComponent::InsideHitBox(SDL_Rect /*OtherHitBox*/)
{

	return true;
}
