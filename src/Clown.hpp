#pragma  once

#include "AnimationPlayer/AnimationPlayer.hpp"
#include "Sprite/Sprite.hpp"

enum class ClownState
{
    IDLE,
    AIM,
    THROW
};

enum class ClownCommands
{
    TRY_IDLE,
    TRY_THROW
};

class Clown : public Sprite
{
    AnimationPlayer AnimPlayer;

    ClownState currentState {};

    void SwitchState(ClownState toState);
    // void LoadAnims();

public:
    Clown();

    void Update();

    void handleEvent();


};