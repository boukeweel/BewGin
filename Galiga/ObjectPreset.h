#pragma once
#include <memory>
#include "GameObject.h"

class ObjectPreset
{
public:
	virtual std::unique_ptr<bew::GameObject>  Create() = 0;
	virtual ~ObjectPreset() = default;
};

class BulletPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
	
};

class PlayerExplotionPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;

};

class ExplotionPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;

};

class BeeEnemyPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
};

class ButterfliesEnemyPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
};

class BossEnemyPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
};

class BossCaptureBeamPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
};

class PlayerHealthIconP1 : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
};

class PlayerHealthIconP2 : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;
};

