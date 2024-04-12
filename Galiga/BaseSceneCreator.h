#pragma once
class BaseSceneCreator
{
public:
	virtual void Load() = 0;

	virtual ~BaseSceneCreator() = default;
};

