#include "ObjectPreset.h"

#include "BulletComponent.h"
#include <TextureComponent.h>

std::unique_ptr<bew::GameObject> BulletPreset::Create()
{
	auto bullet = std::make_unique<bew::GameObject>();
	bullet->AddComponent<bew::TextureComponent>("Bullet.png");
	bullet->AddComponent<BulletComponent>(100.f);
	bullet->SetScale(2, 2);
	return std::move(bullet);
}
