#include "ObjectPreset.h"
#include "BulletComponent.h"
#include <TextureComponent.h>
#include "Animation.h"
#include "AnimatorComponent.h"
#include "BeeEnemyComponent.h"
#include "BossEnemyComponent.h"
#include "ButterfliesEnemyComponent.h"
#include "CaptureBeamComponent.h"
#include "HitBoxComponent.h"
#include "SpriteSheetComponent.h"
#include "HealthComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Texture2D.h"

std::unique_ptr<bew::GameObject> BulletPreset::Create()
{
	auto bullet = std::make_unique<bew::GameObject>();
	bullet->AddComponent<bew::TextureComponent>("Bullet.png");
	bullet->AddComponent<PoolComponent>();
	bullet->AddComponent<BulletComponent>(600.f);
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

std::unique_ptr<bew::GameObject> BeeEnemyPreset::Create()
{
	auto BeeEnemy = std::make_unique<bew::GameObject>();
	BeeEnemy->SetScale(2, 2);
	BeeEnemy->AddComponent<bew::SpriteSheetComponent>("EnemyBees.png", 1, 2);
	BeeEnemy->AddComponent<PoolComponent>();
	
	std::vector<bew::KeyFrame> keyFrames{ {0,0},{0,1} };
	auto animator = BeeEnemy->AddComponent<bew::AnimatorComponent>();
	animator->AddAnimation(std::make_unique<bew::Animation>(BeeEnemy.get(), keyFrames, 0.5, true));
	animator->PlayCurrentAmation();


	BeeEnemy->AddComponent<HealthComponent>(1);
	BeeEnemy->AddComponent<BeeEnemyComponent>();
	BeeEnemy->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });
	return std::move(BeeEnemy);
}

std::unique_ptr<bew::GameObject> ButterfliesEnemyPreset::Create()
{
	auto ButterFlie = std::make_unique<bew::GameObject>();
	ButterFlie->SetScale(2, 2);
	ButterFlie->AddComponent<bew::SpriteSheetComponent>("Butterflies.png", 1, 2);
	ButterFlie->AddComponent<PoolComponent>();

	std::vector<bew::KeyFrame> keyFrames{ {0,0},{0,1} };
	auto animator = ButterFlie->AddComponent<bew::AnimatorComponent>();
	animator->AddAnimation(std::make_unique<bew::Animation>(ButterFlie.get(), keyFrames, 0.5, true));
	animator->PlayCurrentAmation();

	ButterFlie->AddComponent<HealthComponent>(1);
	ButterFlie->AddComponent<ButterfliesEnemyComponent>();
	ButterFlie->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });
	return std::move(ButterFlie);
}

std::unique_ptr<bew::GameObject> BossEnemyPreset::Create()
{
	auto BossEnemy = std::make_unique<bew::GameObject>();
	BossEnemy->SetScale(2, 2);
	BossEnemy->AddComponent<bew::SpriteSheetComponent>("Boss.png", 2, 2);
	BossEnemy->AddComponent<PoolComponent>();

	std::vector<bew::KeyFrame> keyFrames1{ {0,0},{0,1} };
	std::vector<bew::KeyFrame> keyFrames2{ {1,0},{1,1} };
	auto animator = BossEnemy->AddComponent<bew::AnimatorComponent>();
	animator->AddAnimation(std::make_unique<bew::Animation>(BossEnemy.get(), keyFrames1, 0.5, true));
	animator->AddAnimation(std::make_unique<bew::Animation>(BossEnemy.get(), keyFrames2, 0.5, true));

	animator->PlayCurrentAmation();

	BossEnemy->AddComponent<HealthComponent>(2);
	BossEnemy->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -8,-8,16,16 });

	//adding the capture beam
	BossCaptureBeamPreset captureBeamPreset;
	auto captureBeam = captureBeamPreset.Create();

	captureBeam->SetParrent(BossEnemy.get());
	float BeamYpos = static_cast<float>(captureBeam->GetComponent<bew::SpriteSheetComponent>()->GetTexture()->GetSize().y + BossEnemy->GetComponent<bew::SpriteSheetComponent>()->GetTexture()->GetSize().y / 2);
	captureBeam->SetPosition(0, BeamYpos);

	BossEnemy->AddComponent<BossEnemyComponent>(captureBeam->GetComponent<CaptureBeamComponent>());

	captureBeam->SetIsActive(false);

	bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(captureBeam));

	return std::move(BossEnemy);
}

std::unique_ptr<bew::GameObject> BossCaptureBeamPreset::Create()
{
	auto CaptureBeam = std::make_unique<bew::GameObject>();
	CaptureBeam->SetScale(2, 2);
	CaptureBeam->AddComponent<bew::SpriteSheetComponent>("CaptureBeam.png", 1, 3);
	CaptureBeam->AddComponent<CaptureBeamComponent>();
	auto hitbox = CaptureBeam->AddComponent<bew::HitBoxComponent>(SDL_Rect{ -24,-40,48,0 });
	hitbox->SetDrawHitBox(true);

	std::vector<bew::KeyFrame> keyframes{ {0,0},{0,1},{0,2} };

	auto animator = CaptureBeam->AddComponent<bew::AnimatorComponent>();
	animator->AddAnimation(std::make_unique<bew::Animation>(CaptureBeam.get(), keyframes, 0.2f, true));

	//todo add a hitbox

	return std::move(CaptureBeam);
}

std::unique_ptr<bew::GameObject> PlayerHealthIconP1::Create()
{
	auto PlayerHealthIcon = std::make_unique<bew::GameObject>();
	PlayerHealthIcon->SetScale(2, 2);
	PlayerHealthIcon->AddComponent<bew::TextureComponent>("Player1.png");
	return PlayerHealthIcon;
}

std::unique_ptr<bew::GameObject> PlayerHealthIconP2::Create()
{
	auto PlayerHealthIcon = std::make_unique<bew::GameObject>();
	PlayerHealthIcon->SetScale(2, 2);
	PlayerHealthIcon->AddComponent<bew::TextureComponent>("Player2.png");
	return PlayerHealthIcon;
}
