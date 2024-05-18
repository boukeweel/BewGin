#include "ObjectPreset.h"
#include "BulletComponent.h"
#include <TextureComponent.h>
#include "Animation.h"
#include "AnimatorComponent.h"
#include "HitBoxComponent.h"
#include "SpriteSheetComponent.h"

std::unique_ptr<bew::GameObject> BulletPreset::Create()
{
	auto bullet = std::make_unique<bew::GameObject>();
	bullet->AddComponent<bew::TextureComponent>("Bullet.png");
	bullet->AddComponent<PoolComponent>();
	bullet->AddComponent<BulletComponent>(150.f);
	bullet->SetScale(2, 2);
	bullet->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -4,-4,8,8 });
	return std::move(bullet);
}

std::unique_ptr<bew::GameObject> ExplotionPreset::Create()
{
	auto Explotion = std::make_unique<bew::GameObject>();
	Explotion->AddComponent<bew::SpriteSheetComponent>("ExplotionSheet.png", 1, 5);
	std::vector<bew::KeyFrame> keyframes{ {0,0},{0, 1}, { 0, 2 }, { 0, 3 },{ 0, 4 } };
	Explotion->AddComponent<bew::AnimatorComponent>()->AddAnimation(std::make_unique<bew::Animation>(Explotion.get(), keyframes, 0.05, false));
	return std::move(Explotion);
}

std::unique_ptr<bew::GameObject> BeeEnemy::Create()
{
	return std::unique_ptr<bew::GameObject>();
}
