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
    void SetControlsSinglePlayer(bew::InputManager& input, bew::GameObject* player);
    void SetControlsTwoPlayers(bew::InputManager& input, bew::GameObject* player1, bew::GameObject* player2);
};

