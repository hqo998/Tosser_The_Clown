#include "Entities.hpp"

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

#pragma region CROWD_PERSON

CrowdPerson::CrowdPerson() : Sprite("resources/CrowdThrowers/CrowdMemberBASE_spritesheet.png", 13, 2)
{
    Vector2 relativeScale = GetRelativeScale();
    float adjustedScale = (relativeScale.x < relativeScale.y) ? relativeScale.x : relativeScale.y;
    float uniform_scale = .3f * adjustedScale;

    scale = {uniform_scale, uniform_scale};
    position = {540, 540};
    SetOrigin(O_CENTER);

    // LoadAnims();

    SwitchState(CrowdState::IDLE);
}; // CrowdPerson

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
}; // Update

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
}; // SwitchState

#pragma endregion

#pragma region CROWD_MANAGER

void CrowdManager::Update()
{
    for (std::unique_ptr<CrowdPerson> &person : people)
    {
        person->Update();
    }
} // Update

void CrowdManager::Draw()
{
    for (std::unique_ptr<CrowdPerson> &person : people)
    {
        person->Draw();
    }
}; // Draw