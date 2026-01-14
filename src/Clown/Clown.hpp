#pragma  once

#include "../AnimationPlayer/AnimationPlayer.hpp"
#include "../Sprite/Sprite.hpp"

enum ClownState
{
    IDLE,
    AIM,
    THROW
};

enum ClownCommands
{
    TRY_IDLE,
    TRY_THROW
};

class Clown : public Sprite
{
    AnimationPlayer AnimPlayer;

    ClownState currentState = IDLE;

public:
    Clown();

    void Update();

    void handleEvent();
};