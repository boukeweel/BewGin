#pragma once
#include "BaseSceneCreator.h"
#include "GameObject.h"
#include "InputManager.h"

class HighScoreScene :
    public BaseSceneCreator
{
public:
    void Load() override;
private:
    void SetControlsSinglePlayer(bew::InputManager& input, bew::GameObject* player);
    void SetControlsTwoPlayers(bew::InputManager& input, bew::GameObject* player1, bew::GameObject* player2);
};

