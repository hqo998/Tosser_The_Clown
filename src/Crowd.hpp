#pragma once

#include "AnimationPlayer/AnimationPlayer.hpp"
#include "Sprite/Sprite.hpp"

enum class CrowdState
{
    IDLE,
    THROW,
    RELEASE
};

class CrowdPerson : public Sprite
{
    AnimationPlayer AnimPlayer;
    CrowdState currentState {};

    void SwitchState(CrowdState toState);
    // void LoadAnims();
public:
    CrowdPerson();

    void Update();

    void handleEvent();


};

class Crowd
{

};