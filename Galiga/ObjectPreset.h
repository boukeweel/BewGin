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

class ExplotionPreset : public ObjectPreset
{
public:
	std::unique_ptr<bew::GameObject> Create() override;

};



