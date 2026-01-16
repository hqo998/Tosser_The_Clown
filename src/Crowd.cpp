#include "Crowd.hpp"

#pragma region CROWD_ANIMATIONS

AnimationSequence CrowdIdle =
{
        .name = "Idle",
        .startFrame = {0, 0},
        .Length = 3,
        .speedFPS = 5,
        .loop = false,
        .frameHolds = {}
};

#pragma endregion

CrowdPerson::CrowdPerson() : Sprite("resources/CrowdThrowers/CrowdMemberBASE_spritesheet.png", 13, 2)
{
    scale = {2.f, 2.f};
    position = {540, 540};
    SetOrigin(O_CENTER);

    // LoadAnims();

    SwitchState(CrowdState::IDLE);
};

void CrowdPerson::Update()
{
    switch (currentState)
    {
    case CrowdState::IDLE:
        break;

    case CrowdState::THROW:
        break;

    case CrowdState::RELEASE:
        break;
    }

    AnimPlayer.Update();
    SetFrame(AnimPlayer.GetCurrentFrameIndex());
};

void CrowdPerson::SwitchState(CrowdState toState)
{
    currentState = toState;

    switch (toState)
    {
    case CrowdState::IDLE:
        AnimPlayer.PlayAnimation(CrowdIdle);
        break;
    case CrowdState::THROW:
        break;
    case CrowdState::RELEASE:
        break;
    }
};