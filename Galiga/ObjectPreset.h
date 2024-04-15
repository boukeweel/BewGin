#pragma once
#include <memory>

#include "GameObject.h"

class ObjectPreset
{
public:
	virtual std::unique_ptr<bew::GameObject>  Create() = 0;
};

class BulletPreset : public ObjectPreset
{
public:
	BulletPreset(){};

	std::unique_ptr<bew::GameObject> Create() override;
};