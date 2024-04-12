#pragma once
#include "BaseSceneCreator.h"

namespace bew
{
	class GameObject;
	class InputManager;
}

class DemoScene :
    public BaseSceneCreator
{
public:
    void Load() override;

private:
	void SetControllsDemoLevelP1(bew::InputManager& input, bew::GameObject* player);
	void SetControllsDemoLevelP2(bew::InputManager& input, bew::GameObject* player);
};

