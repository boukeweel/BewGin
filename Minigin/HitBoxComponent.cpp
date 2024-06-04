#include "GameObject.h"
#include "Renderer.h"
#include "HitBoxComponent.h"

bew::HitBoxComponent::HitBoxComponent(GameObject* pparentObject, SDL_Rect hitBox) : Component(pparentObject) ,m_hitbox{hitBox}
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

void bew::HitBoxComponent::SetHitBox(SDL_Rect hitbox)
{
	m_hitbox = hitbox;
}

SDL_Rect bew::HitBoxComponent::GetHitBox() const
{
	SDL_Rect hitbox{ m_hitbox };
	glm::vec3 pos = GetParentObject()->GetWorldPosition();
	hitbox.x += static_cast<int>(pos.x);
	hitbox.y += static_cast<int>(pos.y);
	return hitbox;
}

bool bew::HitBoxComponent::InsideHitBox(SDL_Rect OtherHitBox)
{
	SDL_Rect result;
	SDL_Rect OwnHitBox = GetHitBox();
	return SDL_IntersectRect(&OwnHitBox,&OtherHitBox, &result);
}

bool bew::HitBoxComponent::InsideHitBox(GameObject* OtherObject)
{
	return InsideHitBox(OtherObject->GetComponent<HitBoxComponent>()->GetHitBox());
}

