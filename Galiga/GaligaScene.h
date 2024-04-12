#pragma once
#include "BaseSceneCreator.h"

namespace bew
{
	class GameObject;
	class InputManager;
}

class GaligaScene :
    public BaseSceneCreator
{
public:
    void Load() override;

private:
    void SetControllsP1(bew::InputManager& input, bew::GameObject* player);
};

