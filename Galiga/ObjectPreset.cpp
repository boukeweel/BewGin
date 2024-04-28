#include "ObjectPreset.h"

#include "BulletComponent.h"
#include <TextureComponent.h>

#include "HitBoxComponent.h"

std::unique_ptr<bew::GameObject> BulletPreset::Create()
{
	auto bullet = std::make_unique<bew::GameObject>();
	bullet->AddComponent<bew::TextureComponent>("Bullet.png");
	bullet->AddComponent<PoolComponent>();
	bullet->AddComponent<BulletComponent>(100.f);
	bullet->SetScale(2, 2);
	bullet->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -4,-4,8,8 });
	return std::move(bullet);
}
