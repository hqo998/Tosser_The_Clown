#include "Clown.hpp"

#include <print>

// talks on main menu screen
// when playing clicks and drags does throwing idle
// on release does throw animation
// get hit animation?

#pragma region CLOWN_ANIMATIONS

AnimationSequence ClownAniThrow = {
        .name = "Throw",
        .startFrame = {0, 0}, // start frame
        .Length = 9,      // how many frames long
        .speedFPS = 5,      // fps speed
        .loop = false,  // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
};

AnimationSequence clownAniAim = {
        .name = "Aim",
        .startFrame = {0, 0}, // start frame
        .Length = 2,      // how many frames long
        .speedFPS = 5,      // fps speed
        .loop = true,  // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
};

AnimationSequence clownAniTalk = {
        .name = "Talk",
        .startFrame = {0, 1}, // start frame
        .Length = 2,      // how many frames long
        .speedFPS = 2,      // fps speed
        .loop = true,   // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
};
#pragma endregion

void Clown::LoadAnims()
{
    AnimPlayer.AddAnimation(ClownAniThrow);
    AnimPlayer.AddAnimation(clownAniAim);
    AnimPlayer.AddAnimation(clownAniTalk);
};

Clown::Clown()  : Sprite("resources/tmp/TosserSpritesheetTest.png", 9, 2)
{
    scale = {2.f, 2.f};
    position = {540, 540};
    SetOrigin(O_CENTER);

    LoadAnims();

    SwitchState(IDLE);
};

void Clown::Update()
{
    switch (currentState)
    {
    case IDLE:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            SwitchState(AIM);
        }
        break;

    case AIM:
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            SwitchState(THROW);
        }
        break;

    case THROW:
        if (AnimPlayer.Finished())
        {
            SwitchState(IDLE);
        }
        break;
    }

    AnimPlayer.Update();
    SetFrame(AnimPlayer.GetCurrentFrameIndex());
};

void Clown::SwitchState(ClownState toState)
{
    currentState = toState;

    switch (toState)
    {
    case IDLE:
        AnimPlayer.PlayAnimation(clownAniTalk);
        break;
    case AIM:
        AnimPlayer.PlayAnimation(clownAniAim);
        break;
    case THROW:
        AnimPlayer.PlayAnimation(ClownAniThrow);
        break;
    }
};


